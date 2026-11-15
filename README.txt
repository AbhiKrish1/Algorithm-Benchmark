ALGORITHM BENCHMARK

This project compares the runtime of different sorting algorithms and plots the comparison as a graph.

HOW IT WORKS

1. Run the run script in the main folder. It asks you to choose which algorithms you want to compare. Open the root directory in Linux terminal, use the commands:./main/run.sh, give 2 input numbers as prompted. 
2. After you choose, the collect script runs the selected algorithms and uses gprof to measure their running time.
3. The timing data is saved as a dataset.
4. Gnuplot reads the dataset and creates a PNG plot.
5. The dataset, profiled data  and the plot are both stored in the results folder.

HOW TO RUN

1. Go into the project folder. Clone the repository and enter its directory:

git clone https://github.com/AbhiKrish1/Algorithm-Benchmark.git
cd Algorithm-Benchmark

-->On Ubuntu or WSL, install the required tools (Ensure you have NumPy):

sudo apt update
sudo apt install -y build-essential binutils gnuplot-nox python3

2. Make the scripts executable (first time only):

   chmod +x main/run.sh

3. Start the program:

   ./main/run.sh

4. Choose the algorithms when prompted.
5. Wait for it to finish, then open the results folder.

OUTPUT

The results folder contains:
- The dataset file with input size and time taken for each algorithm.
- The PNG plot comparing the chosen algorithms.
- Profiles of the two algorithms so we can compare bottlenecks.

NOTES
- You can also add to the already existing list of algorithms with your own algorithm by saving it in the same function format as the existing algorithms for it to work perfectly (Kindly refer to function format of existing C algorithms).
- A sample of 12 algorithms have been already provided.

Topics Covered

Topic:	Where it is used
1) C programming: The sorting algorithms and the shared runner (algorithms/dataset/)
2) Python: Dataset generation and repeated measurement (main/generate_datasets.py, main/collect.py)
3) Bash: Command Line Automation of the whole project (main/run.sh) and the test script (tests/test.sh)
4) gprof: Profiling the selected algorithms. 
5) GNUplot: Runtime comparison plots 
6) Git:	Collaboration across five team members, with commit history
7) LaTeX: The project report and the Beamer presentation


AI Usage Declaration

We used AI tools to assist with this project. Below we state where, and what our team did with the output.

Automation: AI generated drafts of main/run.sh, main/collect.py and main/generate_datasets.py which we tested.
Sorting algorithms: AI supplied sample implementations of most of the sorting algorithms in order to maintain the particular format which our runner would recognize.. We tested each of them to verify the claim of being optimized or unoptimized.
Tests: AI helped draft the test scripts (tests/test.sh, tests/harness.c). Our team ran and checked them against sort -n.
Report: AI helped generate most of the report which we later reviewed and corrected. We performed all measurements and profiling results and images came from our own runs on our machine.
Profiling and tuning: The idea for the insertion-sort cutoff and alternating buffers came from AI although we did the measurements.
AI also helped to review this project.
