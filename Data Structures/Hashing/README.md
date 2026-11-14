# Hashing

A hash table stores values in an array and uses a **hash function** to decide where each value goes. Instead of searching through every element, you compute the index directly, so insert, search and delete are O(1) on average.

This folder has a hash table in C that uses **open addressing with linear probing**.

## Files

| File | What it is |
|------|------------|
| `Hashing.c` | Hash table with insert, search, delete and print, plus a demo in `main`. |

## How it works

```c
typedef struct {
    int *hashTable;   // the slots
    int N;            // number of slots
} Hash;
```

The hash function is simple:

```c
index = value % N
```

Each slot is in one of three states:

| Value in slot | Meaning |
|---------------|---------|
| `-1` | **Empty**: never used |
| `-2` | **Deleted**: used before, now removed |
| anything else | Holds that value |

### Collisions: linear probing

Two values can hash to the same slot. When that happens, linear probing tries the next slot, then the next, wrapping around at the end of the array:

```c
ind = (probe + i) % N      // i = 0, 1, 2, ...
```

### Why deleted slots exist

Deleting can't just reset a slot to empty. Search stops at the first empty slot, so an empty slot in the middle of a probe chain would hide every value after it. Marking it **deleted** tells search to keep going, while insert is still allowed to reuse the slot.

## Functions

| Function | What it does | Average | Worst case |
|----------|--------------|---------|------------|
| `construct(N)` | Creates a table of N empty slots. | O(N) | O(N) |
| `hash1(h, value)` | Returns `value % N`. | O(1) | O(1) |
| `search(h, value)` | Returns the index of the value, or `-1`. | O(1) | O(N) |
| `insert(h, value)` | Adds the value. Returns 1 on success, 0 if the table is full. | O(1) | O(N) |
| `delete(h, value)` | Marks the value's slot as deleted. | O(1) | O(N) |
| `printHash(h)` | Prints every slot. | O(N) | O(N) |

`insert` calls `search` first, so duplicates are never stored.

## Demo

`main` uses a table of 10 slots and inserts 8, 28, 18, 87, 7. These are the collisions that happen:

| Key | Hashes to | Result |
|-----|-----------|--------|
| 8 | 8 | slot 8 |
| 28 | 8 | taken, so slot 9 |
| 18 | 8 | slots 8 and 9 are taken, so wraps to slot 0 |
| 87 | 7 | slot 7 |
| 7 | 7 | slots 7, 8, 9 and 0 are taken, so slot 1 |

Then it searches for 87 (found at index 7) and 88 (not found), deletes 8, and searches for 28. It still finds 28 at index 9, because the deleted slot doesn't stop the search. Finally it inserts 88, which reuses the deleted slot 8.

Final table:

```
[0] -> 18
[1] -> 7
[2] -> EMPTY
...
[7] -> 87
[8] -> 88
[9] -> 28
```

## Other probing methods

The comments at the bottom of the file describe how to change the probing:

| Method | Probe formula | Notes |
|--------|---------------|-------|
| Linear (the code) | `(probe + i) % N` | Simple, but values pile up in long runs (primary clustering). |
| Quadratic | `(probe + i*i) % N` | Spreads values out more, but may not reach every slot. |
| Double hashing | `(probe + i * hash2(value)) % N` | Needs a second hash function, `q - (value % q)`, where `q` is a prime smaller than N. |

## Build and run

```bash
gcc Hashing.c -o Hashing
./Hashing
```

## Known limitations

- **Negative values are not supported.** In C, `-3 % 10` is `-3`, so the index is negative and the code reads outside the array (undefined behaviour). Also, `-1` and `-2` are the markers for empty and deleted, so they can't be stored as values.
- `insert` returns 1 both for "inserted" and for "already in the table", so the caller can't tell the two apart. It returns 0 only when the table is full.
- The table never resizes. Once it fills up, inserts fail, and performance drops as it gets close to full.
- Deleted slots are never cleaned up, so many deletes slow down searches.
- No function frees the table, and `malloc` is never checked for `NULL`.
- Only `int` values are supported, with no separate keys and values.
- `delete` is a valid function name in C, but it's a reserved word in C++, so this file won't compile as C++.
- Quadratic probing and double hashing are described in comments only, not implemented.
- No separate chaining version yet.

## Concepts practiced

- Hash functions and the modulo operator
- Collisions and open addressing
- Linear probing with wrap-around
- Lazy deletion with a "deleted" marker
- Load factor and why tables need to resize
