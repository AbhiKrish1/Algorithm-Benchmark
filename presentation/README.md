# Project Presentation

`main.tex` is the complete Beamer source for the 16:9 project presentation.
The slides cover the motivation, scope, eleven sorting algorithms, architecture,
dataset generation, common C runner, timing methodology, profiling, outputs,
validation, measured results and conclusion.

The footer displays only the slide number. Team names and roll numbers appear
on the title slide rather than being repeated on every slide.

The benchmark-results slide uses the included reference graph and measurements
for Bubble Sort versus Merge Sort. These were measured in a Linux x86_64
container during report preparation; see `../results/reference_run_20261111/`
and the report for the full environment details.

Compile from this directory:

```bash
pdflatex main.tex
pdflatex main.tex
```
