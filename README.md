<div align="center">

# Data Structures & Algorithms

**Data structures and algorithms built from scratch, with clear explanations, complexity analysis and performance experiments.**

![C](https://img.shields.io/badge/C-data%20structures-00599C?logo=c&logoColor=white)
![Python](https://img.shields.io/badge/Python-algorithms-3776AB?logo=python&logoColor=white)
![Jupyter](https://img.shields.io/badge/Jupyter-notebooks-F37626?logo=jupyter&logoColor=white)

</div>

---

## Overview

This repository is my hands-on study of data structures and algorithms. Every data structure is implemented from scratch in **C**, and the algorithms are explored in **Python notebooks** that time them on real data and chart the results.

Each topic has its own folder with a README that explains how it works, its time and space complexity, and what the code does. You can open any folder on its own, so there's no required reading order.

## What's inside

| Section | Contents | Language |
|---------|----------|----------|
| [**Data Structures**](<Data Structures>) | Stacks, queues, linked lists, trees, heaps and hash tables, plus two projects built on top of them | C |
| [**Algorithms**](<Algorithms>) | Sorting algorithms, compared with timing experiments and charts | Python (Jupyter) |

## Repository structure

```
.
├── Data Structures/
│   ├── Stack/
│   ├── Queue/
│   ├── Linked List/
│   ├── Trees/
│   ├── Heaps/
│   ├── Hashing/
│   ├── Project (1) - Infix To Postfix/
│   └── Project (2) - AVL Dictionary/
└── Algorithms/
    ├── Sorting Analysis (1).ipynb
    └── Sorting Analysis (2).ipynb
```

## Data Structures

| Topic | What's implemented |
|-------|--------------------|
| [Stack](<Data Structures/Stack>) | Array-based stack (LIFO), with infix-to-postfix conversion and postfix evaluation built on it |
| [Queue](<Data Structures/Queue>) | Circular array queue (FIFO) with wrap-around, with a test file |
| [Linked List](<Data Structures/Linked List>) | Singly, doubly and circular doubly linked lists, plus a stack and a queue built on linked lists, each with a test file |
| [Trees](<Data Structures/Trees>) | Binary search tree (insert, search, delete, three traversals) and an AVL tree with rotations |
| [Heaps](<Data Structures/Heaps>) | Array-based max-heap with insert, pop, sift up and sift down |
| [Hashing](<Data Structures/Hashing>) | Hash table using open addressing with linear probing and lazy deletion |

### Projects

| Project | Description |
|---------|-------------|
| [Infix To Postfix](<Data Structures/Project (1) - Infix To Postfix>) | A command-line calculator. It converts an infix expression to postfix and evaluates it, using a stack built on a linked list. |
| [AVL Dictionary](<Data Structures/Project (2) - AVL Dictionary>) | A spell checker. It loads a word list into an AVL tree, checks every word of a sentence, and suggests neighbouring words for any that are missing. |

## Algorithms

| Notebook | What it covers |
|----------|----------------|
| [Sorting Analysis (1)](<Algorithms/Sorting Analysis (1).ipynb>) | Bubble, Selection and Insertion Sort, timed on random lists of up to 50,000 elements |
| [Sorting Analysis (2)](<Algorithms/Sorting Analysis (2).ipynb>) | Adds Merge, Quick and Heap Sort and compares all six, plus a bonus Hybrid Sort |

A quick look at the results, sorting a random list of 50,000 integers:

| Algorithm | Complexity | Time |
|-----------|------------|------|
| Bubble Sort | O(n²) | 118.36 s |
| Insertion Sort | O(n²) | 108.19 s |
| Selection Sort | O(n²) | 33.33 s |
| Heap Sort | O(n log n) | 0.19 s |
| Merge Sort | O(n log n) | 0.12 s |
| Quick Sort | O(n log n) average | 0.045 s |

The notebooks show the full measurements for every list size, along with the charts.

## Roadmap

- [x] Stacks, queues and linked lists
- [x] Trees: binary search tree and AVL tree
- [x] Heaps and hashing
- [x] Sorting algorithms with performance analysis
- [x] Two projects built on these data structures

## How to explore

1. Pick a section above: Data Structures or Algorithms.
2. Open a topic folder and read its README first. It explains the idea, the functions, the complexity, and an example.
3. Open the code or notebook to see the full implementation.
