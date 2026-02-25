import matplotlib.pyplot as plt
import math

sizes = []
merge_times = []

# -------- READ DATA --------
with open("mergesort_comparison.txt", "r") as f:
    next(f)  # Skip header
    for line in f:
        s, t = line.strip().split()
        sizes.append(int(s))
        merge_times.append(float(t))

# -------- THEORETICAL n log n --------
nlogn = [n * math.log2(n) for n in sizes]

# Scale theoretical curve to match actual graph scale
scale_factor = merge_times[-1] / nlogn[-1]*1.1
nlogn_scaled = [x * scale_factor for x in nlogn]

# -------- PLOT --------
plt.figure(figsize=(10, 6))

plt.plot(sizes, merge_times, label="Merge Sort (Experimental)")
plt.plot(sizes, nlogn_scaled, linestyle="dashed", label="Theoretical n log n")

plt.xlabel("Array Size")
plt.ylabel("Time (microseconds)")
plt.title("Merge Sort Time Complexity Analysis")
plt.legend()
plt.grid(True)

plt.show()