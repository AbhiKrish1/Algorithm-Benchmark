# Architecture

The application is divided into independent layers:

- **CLI:** accepts user choices and starts workflows.
- **Algorithms:** contains sorting and searching implementations.
- **Datasets:** creates reproducible input data.
- **Benchmark:** coordinates runs, measures time, and validates results.
- **Profiling:** profiles selected runs separately from normal timing.
- **Results:** writes structured CSV output.
- **Visualization:** invokes GNUplot to create graphs.

The CLI should not contain algorithm implementations. Each layer should expose small functions that can be tested independently.
