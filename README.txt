ALGORITHM BENCHMARK

This project compares the running time of different algorithms and plots the comparison as a graph.

HOW IT WORKS

1. Run the run script in the main folder. It asks you to choose which algorithms you want to compare. Open the root directory in Linux terminal, use the commands:./run.sh, give 2 input numbers as prompted. 
2. After you choose, the collect script runs the selected algorithms and uses gprof to measure their running time.
3. The timing data is saved as a dataset.
4. Gnuplot reads the dataset and creates a PNG plot.
5. The dataset, profiled data  and the plot are both stored in the results folder.

HOW TO RUN

1. Go into the project folder. Clone the repository and enter its directory:

git clone https://github.com/AbhiKrish1/Algorithm-Benchmark.git
cd Algorithm-Benchmark

-->On Ubuntu or WSL, install the required tools:

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
