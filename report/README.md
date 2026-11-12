# Project Report

`main.tex` is the complete LaTeX source for the project report. It documents the
implemented C sorting routines, shared runner, deterministic dataset generator,
median-based timing, separate GNU gprof profiling, GNUplot visualization,
validation checks, limitations and run instructions.

A reference execution comparing `bubble_unoptimized.c` and `merge_optimized.c`
is included under `../results/reference_run_20261111/`. It contains the 19
datasets, `benchmark_data.dat`, runtime graph, gprof reports and environment
metadata. The measured values were collected in a Linux x86_64 container during
report preparation and are explicitly identified as environment-specific.

Compile from this directory:

```bash
pdflatex main.tex
pdflatex main.tex
```

The graph is included from the results directory using a relative path.
