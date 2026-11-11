#!/usr/bin/env bash
# Generate shared datasets, compile two sorting algorithms, measure them, plot,
# and save a separate gprof bottleneck report for each implementation.
set -Eeuo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd -- "$SCRIPT_DIR/.." && pwd)"
ALGORITHMS_DIR="$ROOT_DIR/algorithms/dataset"
RESULTS_DIR="$ROOT_DIR/results"
GENERATOR="$SCRIPT_DIR/generate_datasets.py"
COLLECTOR="$SCRIPT_DIR/collect.py"
RUNNER="$ALGORITHMS_DIR/runner.c"

fail() { printf 'Error: %s\n' "$*" >&2; exit 1; }
usage() {
  cat <<'EOF'
Usage: ./main/run.sh [algorithm-1.c algorithm-2.c]

Choose two C sorting algorithms from algorithms/dataset/ (or pass their paths).
Each source must implement:
  void algorithm(const int *input, int *output, int n);
The same generated integer dataset is given to both implementations at each n.
EOF
}

if [[ "${1:-}" == "-h" || "${1:-}" == "--help" ]]; then usage; exit 0; fi
[[ -f "$GENERATOR" && -f "$COLLECTOR" && -f "$RUNNER" ]] || fail "missing benchmark support file under main/ or algorithms/dataset/"
for tool in python3 gcc gprof gnuplot; do command -v "$tool" >/dev/null 2>&1 || fail "$tool is required"; done
python3 -c 'import numpy' >/dev/null 2>&1 || fail "NumPy is required (python3 -m pip install numpy)"

mapfile -d '' -t candidates < <(find "$ALGORITHMS_DIR" -maxdepth 1 -type f -name '*.c' ! -name 'runner.c' -print0 | sort -z)
if (($# == 2)); then
  selected=("$1" "$2")
elif (($# == 0)); then
  ((${#candidates[@]} >= 2)) || fail "add at least two algorithm source files to $ALGORITHMS_DIR"
  printf 'Available algorithms:\n'
  for i in "${!candidates[@]}"; do printf '  %d) %s\n' "$((i + 1))" "${candidates[$i]##*/}"; done
  selected=()
  for slot in 1 2; do
    while :; do
      read -r -p "Select algorithm $slot (number): " choice
      [[ "$choice" =~ ^[0-9]+$ ]] && ((choice >= 1 && choice <= ${#candidates[@]})) || { echo "Enter a valid number." >&2; continue; }
      picked="${candidates[$((choice - 1))]}"
      if ((slot == 2)) && [[ "$picked" == "${selected[0]}" ]]; then echo "Choose a different algorithm." >&2; continue; fi
      selected+=("$picked")
      break
    done
  done
else
  usage >&2
  exit 2
fi
[[ "${selected[0]}" != "${selected[1]}" ]] || fail "select two different algorithms"

run_id="$(date +%Y%m%d_%H%M%S)"
run_dir="$RESULTS_DIR/run_$run_id"
suffix=1
while [[ -e "$run_dir" ]]; do run_dir="$RESULTS_DIR/run_${run_id}_$suffix"; ((suffix+=1)); done
mkdir -p "$run_dir/bin" "$run_dir/datasets" "$run_dir/profiles"
for i in "${!selected[@]}"; do
  [[ -f "${selected[$i]}" ]] || fail "source file not found: ${selected[$i]}"
  selected[$i]="$(cd -- "$(dirname -- "${selected[$i]}")" && pwd)/$(basename -- "${selected[$i]}")"
done
[[ "${selected[0]}" != "${selected[1]}" ]] || fail "select two different source files"

python3 "$GENERATOR" "$run_dir/datasets"
binaries=()
profile_binaries=()
labels=()
for source in "${selected[@]}"; do
  stem="$(basename -- "$source" .c)"
  labels+=("${stem//_/ }")
  object="$run_dir/bin/$stem.o"
  binary="$run_dir/bin/$stem"
  gcc -std=c11 -O0 -g -Wall -Wextra -c "$source" -o "$object" || fail "compilation failed: $source"
  gcc -std=c11 -O0 -g -Wall -Wextra "$RUNNER" "$object" -o "$binary" || fail "could not link $stem"
  binaries+=("$binary")

  profile_object="$run_dir/bin/${stem}_profile.o"
  profile_binary="$run_dir/bin/${stem}_profile"
  gcc -std=c11 -O0 -g -pg -Wall -Wextra -c "$source" -o "$profile_object" || fail "profile compilation failed: $source"
  gcc -std=c11 -O0 -g -pg "$RUNNER" "$profile_object" -o "$profile_binary" || fail "could not link profile runner for $stem"
  profile_binaries+=("$profile_binary")
done

python3 "$COLLECTOR" "$run_dir/datasets" "$run_dir/benchmark_data.dat" "${binaries[@]}"

# Profile a larger workload separately from timing so instrumentation does not
# change the plotted runtime measurements.
profile_repeats="${ABS_PROFILE_REPEATS:-50}"
[[ "$profile_repeats" =~ ^[1-9][0-9]*$ ]] || fail "ABS_PROFILE_REPEATS must be a positive integer"
profile_dataset="$run_dir/datasets/n_1000.txt"
[[ -f "$profile_dataset" ]] || fail "profile dataset n_1000.txt was not generated"
{ printf '1000 %s\n' "$profile_repeats"; tail -n +2 "$profile_dataset"; } > "$run_dir/profile_input.txt"
for i in 0 1; do
  profile_binary="${profile_binaries[$i]}"
  profile_name="$(basename -- "${selected[$i]}" .c)"
  (cd "$run_dir" && "$profile_binary" < profile_input.txt > /dev/null)
  [[ -s "$run_dir/gmon.out" ]] || fail "gprof data missing for ${labels[$i]}"
  gprof -b "$profile_binary" "$run_dir/gmon.out" > "$run_dir/profiles/${profile_name}_gprof.txt"
  rm -f "$run_dir/gmon.out"
done
rm -f "$run_dir/profile_input.txt"

plot_file="$run_dir/runtime_comparison.png"
gnuplot <<GNUPLOT
set terminal pngcairo size 1200,900 enhanced
set output "$plot_file"
set title "Sorting Algorithm Runtime Comparison"
set xlabel "Dataset size (n)"
set ylabel "Median CPU time per sort (seconds)"
set key outside bottom center vertical spacing 1.5
set grid
set datafile separator whitespace
set logscale y
set format y "10^{%L}"
plot "$run_dir/benchmark_data.dat" using 1:2 with linespoints lw 2 pt 7 title "${labels[0]}", "$run_dir/benchmark_data.dat" using 1:3 with linespoints lw 2 pt 5 title "${labels[1]}"
GNUPLOT
[[ -s "$plot_file" ]] || fail "gnuplot did not produce the plot"
printf '\nBenchmark complete.\nDatasets: %s/datasets\nMeasurements: %s/benchmark_data.dat\nPlot: %s\nProfiles: %s/profiles\n' "$run_dir" "$run_dir" "$plot_file" "$run_dir"
