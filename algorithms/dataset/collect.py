import statistics
import subprocess
import sys
from pathlib import Path

RUNS = 7
TIMEOUT = 120
SIZES = range(100, 1001, 50)


def input_for(dataset):
    lines = dataset.read_text(encoding="ascii").split()
    n = int(lines[0])
    if len(lines) != n + 1:
        raise ValueError(f"invalid dataset: {dataset}")
    # Aim for about one million quadratic comparisons per timed batch.
    repeats = max(10, min(2000, 1_000_000 // max(1, n * n)))
    return n, repeats, f"{n} {repeats}\n" + " ".join(lines[1:]) + "\n"


def measure(program, dataset):
    n, _, payload = input_for(dataset)
    result = subprocess.run(
        [str(program)], input=payload, text=True, capture_output=True,
        timeout=TIMEOUT, check=True,
    )
    try:
        return float(result.stdout.strip().splitlines()[-1])
    except (IndexError, ValueError) as exc:
        raise RuntimeError(f"{program.name} returned no valid timing for n={n}") from exc


def main():
    if len(sys.argv) != 5:
        raise SystemExit("Usage: collect.py DATASET_DIR OUTPUT_FILE PROGRAM1 PROGRAM2")
    dataset_dir, output_path = Path(sys.argv[1]), Path(sys.argv[2])
    programs = [Path(p) for p in sys.argv[3:]]
    rows = []
    for n in SIZES:
        dataset = dataset_dir / f"n_{n}.txt"
        if not dataset.is_file():
            raise SystemExit(f"Missing generated dataset: {dataset}")
        row = [str(n)]
        for program in programs:
            samples = [measure(program, dataset) for _ in range(RUNS)]
            median = statistics.median(samples)
            row.append(f"{median:.12g}")
            print(f"{program.name} n={n}: median {median:.6g} s/sort")
        rows.append(" ".join(row))

    output_path.write_text(
        "n " + " ".join(p.stem for p in programs) + "\n" + "\n".join(rows) + "\n",
        encoding="ascii",
    )
    print(f"Wrote {output_path}")


if __name__ == "__main__":
    main()
