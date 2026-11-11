# Algorithm Benchmarking & Profiling Suite

A modular Python command-line project for comparing sorting and searching algorithms.

## Planned workflow
1. Choose a benchmark from the CLI.
2. Generate reproducible datasets.
3. Run algorithms on equivalent inputs.
4. Measure execution time and validate results.
5. Save measurements to CSV.
6. Profile selected runs separately with `cProfile`.
7. Generate comparison graphs with GNUplot.

## Current status
This archive provides the project architecture and starter placeholders. Algorithm and benchmark implementations will be added incrementally.

## Requirements
- Python 3.10+
- GNUplot (for graph generation)
- `make` and Bash (for the convenience commands)

The core Python implementation is intended to use the Python standard library initially.

## Setup
```bash
python -m venv .venv
source .venv/bin/activate       # Linux/macOS/WSL
# Windows PowerShell: .venv\Scripts\Activate.ps1
pip install -e .
```

## Run
```bash
absuite
# or
python -m absuite.main
```

Bash/Makefile helpers are intended for Linux, macOS, or WSL. On Windows, use WSL or Git Bash with `make` installed.
