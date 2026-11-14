#!/usr/bin/env bash
# Functional tests: every sorting algorithm must produce exactly the same output as `sort -n`
# on several edge-case inputs. This also checks that no elements are lost or changed
# (the runner only checks ordering, so this closes that gap).
# Usage: ./tests/test.sh            (run from the project root)
set -uo pipefail

ROOT="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
ALGS="$ROOT/algorithms/dataset"
TMP="$(mktemp -d)"
trap 'rm -rf "$TMP"' EXIT

# ---- build the test inputs (non-negative ints, as radix sort requires) ----
mkdir -p "$TMP/in"
make_case() { # name, then values on stdin
  local f="$TMP/in/$1.txt" vals
  vals="$(cat)"
  { if [[ -z "$vals" ]]; then echo 0; else echo "$(wc -w <<<"$vals")"; echo "$vals"; fi; } > "$f"
}
echo -n ""                          | make_case empty
echo "42"                           | make_case single
echo "5 5 5 5 5 5"                  | make_case all_equal
echo "3 1 2"                        | make_case three
echo "1 2 3 4 5 6 7 8 9 10"         | make_case already_sorted
echo "10 9 8 7 6 5 4 3 2 1"         | make_case reversed
echo "4 1 4 2 1 3 3 2 0 0 999999"   | make_case duplicates
python3 -c "import random;random.seed(1);print(*[random.randrange(1000000) for _ in range(1000)])" | make_case random_1000
python3 -c "import random;random.seed(2);print(*[random.randrange(5) for _ in range(500)])"          | make_case many_duplicates_500

pass=0; fail=0
for src in "$ALGS"/*.c; do
  name="$(basename "$src" .c)"
  [[ "$name" == "runner" ]] && continue
  if ! gcc -std=c11 -O0 -Wall -Wextra "$ROOT/tests/harness.c" "$src" -o "$TMP/$name" 2> "$TMP/$name.err"; then
    echo "FAIL  $name (compile error)"; cat "$TMP/$name.err"; ((fail++)); continue
  fi
  ok=1
  for input in "$TMP"/in/*.txt; do
    case_name="$(basename "$input" .txt)"
    "$TMP/$name" < "$input" > "$TMP/actual.txt"
    tail -n +2 "$input" | tr ' ' '\n' | grep -v '^$' | sort -n > "$TMP/expected.txt"
    if ! cmp -s "$TMP/actual.txt" "$TMP/expected.txt"; then
      echo "FAIL  $name on case '$case_name'"; ok=0
    fi
  done
  if ((ok)); then echo "PASS  $name"; ((pass++)); else ((fail++)); fi
done

echo "----"; echo "Passed: $pass   Failed: $fail"
((fail == 0))