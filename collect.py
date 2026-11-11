import os
import sys
import subprocess
import numpy as np
import pandas as pd

REPEAT = 10000   # must match the number in the C loop
RUNS = 3         # runs per n, to average noise
TIMEOUT = 120    # seconds allowed for one run


def get_time(prog, n):
    """Run prog with input n. Return gprof time of algorithm (seconds)."""
    if os.path.exists("gmon.out"):
        os.remove("gmon.out")

    subprocess.run(
        [prog],
        input=str(n),
        text=True,
        stdout=subprocess.DEVNULL,
        timeout=TIMEOUT,
    )

    report = subprocess.run(
        ["gprof", "-b", "-p", prog, "gmon.out"],
        capture_output=True,
        text=True,
    ).stdout

    for line in report.splitlines():
        parts = line.split()
        if parts and parts[-1] == "algorithm":
            return float(parts[2])   # column 3 = self seconds
    return 0.0                       # function not seen = too fast


def main():
    progs = sys.argv[1:]             # example: ./prog1 ./prog2
    ns = np.arange(100, 1100, 100)   # same n list for all programs

    table = pd.DataFrame({"n": ns})

    for prog in progs:
        name = os.path.basename(prog)
        times = []
        timed_out = False

        for n in ns:
            if timed_out:
                times.append(np.nan)   # skip larger n after a timeout
                continue
            try:
                runs = [get_time(prog, int(n)) for _ in range(RUNS)]
                mean_total = np.mean(runs)
                times.append(mean_total / REPEAT)   # time of one call
                print(name, n, mean_total / REPEAT)
            except subprocess.TimeoutExpired:
                timed_out = True
                times.append(np.nan)

        table[name] = times

    table.to_csv("data.txt", sep=" ", index=False, na_rep="")
    print("Wrote data.txt")


main()
