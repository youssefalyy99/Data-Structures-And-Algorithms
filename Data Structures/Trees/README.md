# Trees

A tree is a hierarchy of **nodes**. Each node holds a value and links to child nodes. In a **binary tree**, every node has at most two children: `left` and `right`.

This folder has two C programs:

- a **Binary Search Tree** (BST)
- an **AVL tree**, which is a BST that is meant to keep itself balanced

## Files

| File | What it is |
|------|------------|
| `BinarySearchTree.c` | BST with insert, search, find-min, delete and three traversals. |
| `AVLtrees.c` | AVL tree with insert and rotations. Work in progress. |

The files don't include each other. They both define their own `Node`, `insert` and `main`, so compile each one on its own, never together.

## Binary Search Tree

The rule: for every node, everything in its **left** subtree is smaller, and everything in its **right** subtree is larger.

```
        10
       /  \
      5    15
     / \   / \
    2   7 12  20
```

```c
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;
```

### Functions

| Function | What it does | Average | Worst case |
|----------|--------------|---------|------------|
| `insert(root, key)` | Adds a value. Duplicates are ignored. | O(log n) | O(n) |
| `searchRecursive(root, val)` | Returns the node with that value, or `NULL`. | O(log n) | O(n) |
| `FindMin(root)` | Returns the leftmost node. | O(log n) | O(n) |
| `Delete(root, data)` | Removes a value and returns the new root. | O(log n) | O(n) |
| `PreOrder` / `InOrder` / `PostOrder` | Print every value. | O(n) | O(n) |

The worst case happens when values are inserted in sorted order. The tree becomes a chain, like a linked list, and its height is n.

### Delete: the three cases

1. **Leaf (no children):** free the node.
2. **One child:** replace the node with its child.
3. **Two children:** copy the smallest value from the right subtree into the node, then delete that value from the right subtree.

### Traversals

| Traversal | Order | Use |
|-----------|-------|-----|
| PreOrder | node, left, right | copying a tree |
| InOrder | left, node, right | gives the values **sorted** |
| PostOrder | left, right, node | deleting a tree |

### Demo output

`main` inserts 10, 5, 15, 2, 7, 12, 20 and prints:

```
PreOrder Traversal: 10 5 2 7 15 12 20
InOrder Traversal: 2 5 7 10 12 15 20
PostOrder Traversal: 2 7 5 12 20 15 10
```

## AVL Tree

An AVL tree is a BST with one extra rule: for every node, the heights of its left and right subtrees differ by at most 1. When an insert breaks that rule, the tree is fixed with **rotations**. This keeps the height at O(log n), so insert and search stay O(log n) even for sorted input.

```c
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;           // height of the subtree rooted here (a leaf is 1)
} Node;
```

### What's in the file

| Function | What it does |
|----------|--------------|
| `newNode(data)` | Creates a node with height 1. |
| `height(n)` | Returns a node's height, or 0 for `NULL`. |
| `max(a, b)` | Larger of two numbers. |
| `getBalance(n)` | Meant to return left height minus right height. |
| `rightRot(y)` / `leftRot(x)` | The two basic rotations. |
| `insert(root, val)` | BST insert, then update height, then rebalance. |

### The four rebalancing cases

| Case | Imbalance | Fix |
|------|-----------|-----|
| LL | inserted into the left child's left side | right rotation |
| RR | inserted into the right child's right side | left rotation |
| LR | inserted into the left child's right side | left rotation on the left child, then right rotation |
| RL | inserted into the right child's left side | right rotation on the right child, then left rotation |

## Build and run

```bash
gcc BinarySearchTree.c -o BinarySearchTree
./BinarySearchTree
```

`AVLtrees.c` compiles, but its `main` is empty, so running it prints nothing.

## Known limitations

### AVLtrees.c: the tree does not balance yet

I tested it: inserting 1, 2, 3 leaves 1 as the root, and inserting 1 to 100 in order gives a tree of height 100, which is a chain. Two typos in the code cause this:

- `getBalance` computes `height(n->left) - height(n->left)`, which is always 0. It should subtract the **right** height, so no rotation ever runs.
- In `insert`, the height update uses `height(root->left)` twice, so the right subtree is never counted. It should use the left and the right.

The rotation functions themselves follow the standard algorithm.

Other gaps in `AVLtrees.c`:
- `main` is empty.
- No delete, search, or traversal functions.
- `max` has no `return` at the end, so the compiler warns about it.

### BinarySearchTree.c

- `main` only demonstrates the traversals. Search, `FindMin` and `Delete` aren't called anywhere.
- Duplicate values are silently ignored.
- The tree is never freed, and `malloc` is never checked for `NULL`.
- Only `int` values are supported.
- The tree doesn't balance itself, so sorted input gives a chain. That's the problem the AVL tree is meant to solve.

## Concepts practiced

- Recursion on tree structures
- BST insert, search and delete (including the two-children case)
- Preorder, inorder and postorder traversal
- Tree height and balance factor
- AVL rotations (LL, RR, LR, RL)
