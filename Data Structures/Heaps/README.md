# Heaps

A heap is a binary tree stored in an array that always keeps the largest (or smallest) value at the top. It's the structure behind priority queues and heap sort.

This folder has an array-based **max-heap** in C: the largest value is always at the root.

## Files

| File | What it is |
|------|------------|
| `Heaps.c` | Max-heap with insert, pop and the helper functions that keep the heap property, plus a demo in `main`. |

## How the heap works

A heap is a complete binary tree, so it fits in a plain array with no pointers. For the element at index `i`:

| Relation | Index |
|----------|-------|
| Parent | `(i - 1) / 2` |
| Left child | `2 * i + 1` |
| Right child | `2 * i + 2` |

The **max-heap rule:** every parent is greater than or equal to its children.

```
Array:  [90, 70, 50, 10, 30, 20]

Tree:           90
              /    \
            70      50
           /  \    /
         10   30  20
```

```c
typedef struct {
    int arr[100];   // storage, fixed capacity of 100
    int n;          // number of elements currently in the heap
} Heap;
```

## Functions

| Function | What it does | Time |
|----------|--------------|------|
| `newHeap()` | Allocates an empty heap (`n = 0`). | O(1) |
| `insertHeap(h, val)` | Adds `val` at the end, then calls `shiftUp`. | O(log n) |
| `shiftUp(arr, i)` | Swaps an element with its parent while it's bigger than the parent. | O(log n) |
| `pop(h)` | Removes the root: moves the last element to the top, then calls `shiftDown`. | O(log n) |
| `shiftDown(arr, n, i)` | Swaps an element with its larger child until the heap rule holds again. | O(log n) |
| `swap(arr, i, j)` | Swaps two elements of the array. | O(1) |

Space is O(n), with a fixed maximum of 100 elements.

### Insert

1. Put the new value in the first free slot at the end of the array.
2. Compare it to its parent. If it's bigger, swap them.
3. Repeat until it's no longer bigger than its parent, or it reaches the root.

### Pop

1. Decrease `n` by one.
2. Copy the last element into the root, overwriting the old maximum.
3. Sift it down: compare it with both children, swap with the larger one if that child is bigger, and repeat.

## Demo

`main` inserts 50, 30, 70, 10, 90, 20, then pops the maximum twice, printing the array each time. The output is:

```
Heap after insertion:
90 70 50 10 30 20

Popped: 90
Heap after first pop:
70 30 50 10 20

Popped: 70
Heap after second pop:
50 30 20 10
```

Because `pop` returns nothing, `main` reads `h->arr[0]` just before each pop to see the value being removed.

How the first pop works: the last element (20) moves to the root, giving `20 70 50 10 30`. Then 20 swaps with its larger child, 70, and then with its larger child, 30, which gives `70 30 50 10 20`.

## Build and run

```bash
gcc Heaps.c -o Heaps
./Heaps
```

## Testing

Besides the demo, I ran a stress test: 2000 random heaps of 1 to 100 values, including negatives and duplicates. After every insert and every pop, every parent was at least as big as its children. Popping everything gave the values in descending order every time. The test found no problems.

## Known limitations

- **No capacity check.** `insertHeap` doesn't check whether the heap is full. The 101st insert writes past the end of `arr` and lands on the `n` field right after it, which corrupts the heap. In a test, 101 inserts left `n` at 8 instead of 101.
- `pop` returns `void`, so the removed maximum is lost unless you read `arr[0]` first, as `main` does. There's also no `peek` function.
- `malloc` isn't checked for `NULL`.
- Only `int` values are supported, with a fixed capacity of 100.
- Only a max-heap. There's no min-heap, no heap sort, and no function to build a heap from an existing array.
- `main` reads the array directly instead of using a print function.

## Concepts practiced

- A binary tree stored in an array
- Parent and child index formulas
- Sift up and sift down
- Priority queue behavior
