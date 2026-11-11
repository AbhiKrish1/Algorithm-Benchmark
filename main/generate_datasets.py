#!/usr/bin/env python3
"""Generate reproducible integer datasets for the benchmark suite."""
import argparse
import random
from pathlib import Path


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("output_dir", type=Path)
    parser.add_argument("--start", type=int, default=100)
    parser.add_argument("--stop", type=int, default=1000)
    parser.add_argument("--step", type=int, default=50)
    parser.add_argument("--seed", type=int, default=2026)
    args = parser.parse_args()

    if args.start < 1 or args.stop < args.start or args.step < 1:
        parser.error("sizes must be positive and stop must be at least start")

    args.output_dir.mkdir(parents=True, exist_ok=True)
    sizes = list(range(args.start, args.stop + 1, args.step))
    if sizes[-1] != args.stop:
        sizes.append(args.stop)

    for n in sizes:
        rng = random.Random(args.seed + n)
        values = [rng.randrange(0, 1_000_000) for _ in range(n)]
        path = args.output_dir / f"n_{n}.txt"
        path.write_text(f"{n}\n" + " ".join(map(str, values)) + "\n", encoding="ascii")
    print(f"Generated {len(sizes)} datasets in {args.output_dir}")


if __name__ == "__main__":
    main()
