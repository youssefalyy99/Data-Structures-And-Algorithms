# Data Structures Training

My collection of data structures, built from scratch in C. Each topic has its own folder with the code and its own README that explains how it works.

## Contents

| Topic | What's inside |
|-------|---------------|
| [Stack](<Stack/>) | Array-based stack (LIFO), plus infix-to-postfix conversion and postfix evaluation built on it. |
| [Queue](<Queue/>) | Circular array queue (FIFO) with wrap-around, and a test file. |
| [Linked List](<Linked List/>) | Singly, doubly and circular doubly linked lists, plus a stack and a queue built on linked lists, each with a test file. |
| [Trees](<Trees/>) | Binary search tree (insert, search, delete, three traversals) and an AVL tree with rotations. |
| [Heaps](<Heaps/>) | Array-based max-heap with insert, pop, sift up and sift down. |
| [Hashing](<Hashing/>) | Hash table using open addressing with linear probing, and lazy deletion. |

## Projects

| Project | What it is |
|---------|------------|
| [Project (1) - Infix To Postfix](<Project (1) - Infix To Postfix/>) | A command-line calculator. It converts an infix expression to postfix and evaluates it, using a stack built on a linked list. |
| [Project (2) - AVL Dictionary](<Project (2) - AVL Dictionary/>) | A spell checker. It loads a word list into an AVL tree, checks each word of a sentence, and suggests the neighbouring words for any that are missing. |

## Folder layout

```
Data Structures/
├── README.md
├── Stack/
├── Queue/
├── Linked List/
├── Trees/
├── Heaps/
├── Hashing/
├── Project (1) - Infix To Postfix/
└── Project (2) - AVL Dictionary/
```

## The topics at a glance

**Stack.** Last in, first out. You can only add and remove at the top. It's used for undo, expression parsing and function calls. Here it powers the infix-to-postfix converter.

**Queue.** First in, first out. Items are added at the rear and removed from the front. The circular version reuses the array space by wrapping around.

**Linked List.** Elements live in separate nodes connected by pointers, so adding or removing at the ends doesn't shift anything. The folder covers three kinds (singly, doubly, circular doubly) and shows how a stack and a queue can be built on top of a list.

**Trees.** A hierarchy of nodes. A binary search tree keeps smaller values on the left and larger ones on the right, which makes search fast. An AVL tree adds rotations to keep the tree balanced.

**Heaps.** A binary tree stored in an array, with the largest value always at the root. It's the basis of priority queues and heap sort.

**Hashing.** A hash function turns a value into an array index, giving fast lookups. Collisions are handled by probing for the next free slot.

## Cost cheat sheet

Typical costs for each structure as it's designed to work. The topic READMEs say what each file actually implements.

| Structure | Insert | Delete | Search |
|-----------|--------|--------|--------|
| Stack (array) | O(1) | O(1) | O(n) |
| Queue (circular array) | O(1) | O(1) | O(n) |
| Singly linked list | O(1) at the front, O(n) at the end | O(1) at the front, O(n) at the end | O(n) |
| Circular doubly linked list | O(1) at either end | O(1) at either end | O(n) |
| Binary search tree | O(log n) average, O(n) worst | O(log n) average, O(n) worst | O(log n) average, O(n) worst |
| AVL tree | O(log n) | O(log n) | O(log n) |
| Max-heap | O(log n) | O(log n) for the max | O(n), but the max is available in O(1) |
| Hash table (linear probing) | O(1) average, O(n) worst | O(1) average, O(n) worst | O(1) average, O(n) worst |

## Language

Everything here is written in C.
