# Algorithms

Algorithm implementations and performance experiments, written as Jupyter notebooks in Python. Each notebook explains an algorithm, implements it, times it on real data, and charts the results.

## Notebooks

| Notebook | What it covers |
|----------|----------------|
| [Sorting Analysis (1)](<Sorting Analysis (1).ipynb>) | Bubble Sort, Selection Sort and Insertion Sort, timed on random lists from 10K to 50K elements. |
| [Sorting Analysis (2)](<Sorting Analysis (2).ipynb>) | Adds Merge Sort, Quick Sort and Heap Sort, and compares all six on the same lists. Also has a bonus Hybrid Sort. |

## How the experiments work

Both notebooks follow the same steps:

1. **Generate data.** Random integer lists of 20, 10K, 20K, 30K, 40K and 50K elements.
2. **Implement the algorithms.** Each one has a short explanation of its approach and complexity above its code.
3. **Time them.** Each algorithm is run on a copy of every list and timed with `time.perf_counter()`.
4. **Plot the results.** Matplotlib line charts compare execution time against list size.

The slow algorithms take minutes on the large lists, so the measured times are saved in dictionaries inside the notebook. That way the chart can be redrawn instantly without running everything again.

## The algorithms

| Algorithm | Approach | Time | Extra space |
|-----------|----------|------|-------------|
| Bubble Sort | Swap neighbouring elements that are out of order | O(n²) | O(1) |
| Selection Sort | Find the minimum of the unsorted part, put it first | O(n²) | O(1) |
| Insertion Sort | Insert each element into the sorted part | O(n²) | O(1) |
| Merge Sort | Divide in halves, sort each, merge | O(n log n) | O(n) |
| Quick Sort | Random pivot, partition, sort both sides | O(n log n) average, O(n²) worst | O(log n) average |
| Heap Sort | Build a max-heap, repeatedly move the max to the end | O(n log n) | O(1) |
| Hybrid Sort *(bonus)* | Merge Sort that switches to Selection Sort for pieces of 16 elements or fewer | O(n log n) | O(n) |

Heap Sort builds on the [max-heap](<../Data Structures/Heaps>) from the Data Structures section.

## Results

Execution time in seconds, from the recorded measurements in `Sorting Analysis (2)`:

| List size | Bubble | Insertion | Selection | Merge | Heap | Quick |
|-----------|--------|-----------|-----------|-------|------|-------|
| 10K | 3.71 | 3.39 | 1.18 | 0.039 | 0.039 | 0.017 |
| 20K | 14.97 | 15.08 | 4.77 | 0.063 | 0.047 | 0.024 |
| 30K | 37.76 | 32.82 | 10.96 | 0.059 | 0.070 | 0.033 |
| 40K | 71.42 | 64.05 | 19.91 | 0.082 | 0.104 | 0.044 |
| 50K | 118.36 | 108.19 | 33.33 | 0.120 | 0.190 | 0.045 |

What the numbers show:

- **The jump from O(n²) to O(n log n) is huge.** On 50,000 elements, Bubble and Insertion Sort take close to two minutes. Merge, Heap and Quick Sort finish in under 0.2 seconds.
- **Quadratic growth is easy to see.** Doubling the list from 10K to 20K makes Bubble Sort about 4 times slower (3.71 s to 14.97 s), as O(n²) predicts.
- **Selection Sort is the fastest of the three quadratic sorts.** It has the same complexity, but it does at most one swap per pass, while Bubble and Insertion Sort swap for every out-of-order pair.
- **Quick Sort was the fastest overall** on this data.

Times vary a little between runs, because each run uses new random lists.

## Libraries

- `random` to generate the data
- `time` to measure execution time
- `matplotlib` to plot the results

## Concepts practiced

- Comparison-based sorting and time and space complexity
- Divide and conquer (Merge Sort, Quick Sort)
- Heap-based sorting
- Benchmarking code and visualizing the results
- Combining two algorithms into a hybrid
