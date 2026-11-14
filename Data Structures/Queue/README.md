# Queue

A queue follows **FIFO** (First In, First Out): the first item added is the first one removed. Think of a line at a shop.

This folder has an array-based **circular queue** in C.

## Files

| File | What it is |
|------|------------|
| `queue.c` | The queue implementation, with a small demo in `main`. |

## How the queue works

```c
typedef struct {
    int arr[100];   // storage, fixed capacity of 100
    int front;      // index of the first element, -1 when empty
    int rear;       // index of the last element, -1 when empty
} queue;
```

The queue is **circular**: when `rear` reaches the end of the array, it wraps around to index 0 using `% 100`. This lets freed space at the front be reused, so the queue doesn't "run out" after 100 enqueues the way a plain array queue would.

| Function | What it does | Time |
|----------|--------------|------|
| `initialize()` | Allocates a queue and sets `front = rear = -1` | O(1) |
| `enqueue(q, x)` | Adds `x` at the rear | O(1) |
| `dequeue(q)` | Removes and returns the front value (`-1` if empty) | O(1) |
| `isEmpty(q)` | Returns 1 if the queue has no elements | O(1) |
| `isFull(q)` | Returns 1 if the queue holds 100 elements | O(1) |

Space is O(n), with a fixed maximum of 100 elements.

### Empty and full

- **Empty:** `front == -1` and `rear == -1`.
- **Full:** `(rear + 1) % 100 == front`, meaning the next rear position is the front.
- When the last element is dequeued, both `front` and `rear` are reset to `-1`.

## Demo

`main` enqueues 10, 20, 30, dequeues two values, enqueues 40, then dequeues the rest. The output is:

```
10
20
30
40
```

## Build and run

```bash
gcc queue.c -o queue
./queue
```

## Known limitations

- `enqueue` does not check `isFull`, so enqueuing into a full queue overwrites the front element and breaks the queue.
- `dequeue` returns `-1` on an empty queue, which can't be told apart from a real `-1` stored in the queue.
- The memory from `initialize` is never freed.
- The result of `malloc` is not checked for `NULL`.
- Only `int` values are supported, with a fixed capacity of 100.

## Concepts practiced

- FIFO behavior
- Circular array with modulo wrap-around
- Telling empty and full apart
