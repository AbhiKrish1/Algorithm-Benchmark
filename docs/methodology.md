# Benchmark Methodology

1. Use the same logical input for each algorithm being compared.
2. Give each sorting algorithm its own copy so in-place sorting does not affect later runs.
3. Repeat measurements and report a clearly defined statistic (for example, median).
4. Use `time.perf_counter()` for elapsed-time measurements.
5. Validate every result; never treat speed as success if output is incorrect.
6. Keep profiler runs separate from ordinary timing because profiling adds overhead.
7. Record dataset type, input size, repeat count, Python version, and measurement units.
8. Binary search must receive sorted input.
