# Linked List

A linked list stores its elements in separate **nodes**. Each node holds a value and a pointer to the next node (and, in some variants, the previous one). Unlike an array, the elements are not next to each other in memory, so inserting and removing at the ends doesn't require shifting anything.

This folder has five C programs. Each one is a standalone file with its own `main`.

## Files

| File | What it is |
|------|------------|
| `LinkedList.c` | Singly linked list. |
| `DoublyLinkedList.c` | Doubly linked list (each node has `next` and `prev`). |
| `DoubleCircularLinkedList.c` | Circular doubly linked list (the last node links back to the first). |
| `StackLinkedList.c` | Stack built on a singly linked list. |
| `QueueLinkedList.c` | Queue built on a singly linked list. |

The files don't include each other, and they all define their own `Node` and `initialize`. Compile each one separately, never together.

## The three list types

```
Singly:    head -> [1|•]-> [2|•]-> [3|NULL]

Doubly:    NULL <- [1] <-> [2] <-> [3] -> NULL

Circular:  ┌-> [1] <-> [2] <-> [3] <-┐
           └-------------------------┘   (3's next is 1, 1's prev is 3)
```

### Operations

| Operation | Singly | Doubly | Circular doubly |
|-----------|--------|--------|-----------------|
| `insertAtBeginning` | O(1) | O(1) | O(1) |
| `insertAtEnd` | O(n) | O(n) | O(1) |
| `deleteFromBeginning` | O(1) | O(1) | O(1) |
| `deleteFromEnd` | O(n) | O(n) | O(1) |
| `display` | O(n) | O(n) | O(n) |

The circular version gets O(1) at the end because `head->prev` is always the tail. The other two walk from the head to find the last node.

## Stack and queue on a linked list

### `StackLinkedList.c`

Keeps two pointers: `start` (the first node) and `top` (the last node). `push` adds after `top` in O(1). `pop` has to walk from `start` to find the node before `top`, so it is O(n). Keeping `top` at the head of the list instead would make both operations O(1).

### `QueueLinkedList.c`

Keeps `front` and `rear` pointers. `enqueue` adds at `rear` and `dequeue` removes from `front`, both in O(1). Unlike the array queue, it has no fixed capacity.

## Demo output

Each file's `main` runs a small demo. The values it prints:

| File | Output |
|------|--------|
| `LinkedList.c` | `1 2 3`, then `7 8 9 1 2 3`, then `8 9 1 2` |
| `DoublyLinkedList.c` | `3 2 1 99` |
| `DoubleCircularLinkedList.c` | `3 2 1 99` |
| `StackLinkedList.c` | `1 2 6 7` (bottom to top) |
| `QueueLinkedList.c` | `4` |

## Build and run

Compile each file on its own:

```bash
gcc LinkedList.c -o LinkedList
./LinkedList
```

The same works for the other four files.

## Known limitations

- **`QueueLinkedList.c`:** `initialize()` and `newnode()` don't have a `return` statement. This is undefined behaviour. It happens to work when compiled without optimization (`gcc QueueLinkedList.c`), but crashes with a segmentation fault when compiled with `-O2`.
- **`StackLinkedList.c`:** popping the last remaining element uses an uninitialized `prev` pointer, which is undefined behaviour. The demo never pops down to one element, so it doesn't show up there.
- **`DoubleCircularLinkedList.c`:** `display` on an empty list crashes, because it reads `head->data` before checking for `NULL`.
- **`LinkedList.c`:** `insertAtEnd` allocates an extra `Node` called `temp` and then overwrites the pointer, leaking memory on every call.
- `dequeue` and `pop` return nothing, so the removed value is lost.
- None of the lists have a free function, and `malloc` is never checked for `NULL`.
- No search, insert at a position, delete by value, or reverse yet.
- Only `int` values are supported.

## Concepts practiced

- Dynamic memory with `malloc` and `free`
- Pointer manipulation: head, tail, `prev` and `next`
- Edge cases: empty list, single element
- Singly, doubly and circular lists
- Building a stack and a queue on top of a list
