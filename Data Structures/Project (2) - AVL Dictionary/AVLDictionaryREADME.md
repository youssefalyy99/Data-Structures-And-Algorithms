# AVL Tree Dictionary (Spell Checker)

A small spell checker built on an **AVL tree**. It loads a word list from a file into a self-balancing tree, reads a sentence from the user, and checks every word against the dictionary. For a word that isn't found, it prints the words around it as suggestions.

## Files

| File | What it is |
|------|------------|
| `AVLDictionary.c` | The whole program. |
| `Dictionary.txt` | The word list. **You provide this file.** It must be in the folder you run the program from. |

`Dictionary.txt` is plain text with words separated by spaces or new lines, for example one word per line. The order doesn't matter.

## How it works

1. **Load.** The tree starts with one hard-coded word, `mango`. Then every word in `Dictionary.txt` is inserted. After each insert the tree rebalances itself, so it stays shallow.
2. **Read.** The program asks for a sentence and splits it into words at spaces.
3. **Check.** Each word is searched for in the tree. It prints `CORRECT` if it's found.
4. **Suggest.** If it isn't found, the program prints `INCORRECT` followed by three words: the last word the search visited, that word's **successor** (next word alphabetically) and its **predecessor** (previous word).

### Why the suggestions make sense

When a search for a missing word falls off the tree, the last node it visited is always either the word just before it or the word just after it alphabetically. Its successor and predecessor then cover the other side. So the two real neighbours of the misspelled word are always among the three printed words.

### Example run

With a 10-word dictionary (`apple banana cherry date elderberry fig grape mango kiwi lemon`), the sentence `apple kiwi bananaa` gives:

```
===== AVL TREE DICTIONARY =====
>> Dictinary Loaded Successfully . . .
>> Tree Height : 4
>> Size : 10
==============================
Enter A Sentence: apple kiwi bananaa
>> apple - CORRECT
>> kiwi - CORRECT
>> bananaa - INCORRECT , cherry - date - banana
```

`bananaa` is missing. The search stopped at `cherry`, whose successor is `date` and predecessor is `banana`. The real neighbours of `bananaa` are `banana` and `cherry`, and both are in the list.

## The AVL tree

An AVL tree is a binary search tree where, for every node, the heights of its left and right subtrees differ by at most 1. When an insert breaks that rule, the tree is fixed with rotations. This keeps the height at O(log n), even when the words are inserted in alphabetical order, which would turn a plain BST into a linked list.

```c
typedef struct Node {
    char word[50];          // the word (up to 49 characters)
    struct Node* left;
    struct Node* right;
    int height;             // height of the subtree rooted here (a leaf is 1)
} Node;
```

Words are compared with `strcmp`, so the tree is ordered alphabetically (by character code).

I tested the balancing: loading 1000 words in sorted order gives a tree of height 10, which is the best possible for 1000 nodes. The balancing works correctly in this file.

### The four rebalancing cases

| Case | Imbalance | Fix |
|------|-----------|-----|
| LL | new word went into the left child's left side | right rotation |
| RR | new word went into the right child's right side | left rotation |
| LR | new word went into the left child's right side | left rotation on the left child, then right rotation |
| RL | new word went into the right child's left side | right rotation on the right child, then left rotation |

## Functions

| Function | What it does | Time |
|----------|--------------|------|
| `newNode(txt)` | Creates a node holding the word, with height 1. | O(1) |
| `insert(root, txt)` | Inserts a word, updates heights, rebalances. Duplicates are ignored. | O(log n) |
| `leftRotation` / `rightRotation` | The two basic rotations. | O(1) |
| `height(root)` | Height of a subtree, 0 for `NULL`. | O(1) |
| `balanceFactor(root)` | Left height minus right height. | O(1) |
| `max1(a, b)` | Larger of two numbers. | O(1) |
| `DictionaryToTree(root)` | Reads `Dictionary.txt` and inserts every word. | O(n log n) |
| `search(root, txt)` | Looks up a word, prints `CORRECT` or `INCORRECT` plus suggestions. | O(log n) |
| `findMin(root)` / `findMax(root)` | Smallest / largest word in a subtree. | O(log n) |
| `successorNode(current, root)` | The next word alphabetically. | O(log n) |
| `predecessorNode(current, root)` | The previous word alphabetically. | O(log n) |
| `searchForSuc` / `searchForPre` | Helpers that find the successor / predecessor from above when the node has no right / left child. | O(log n) |
| `inOrder(root)` | Prints all words in alphabetical order. Not called by `main`. | O(n) |

The times for word-based operations also include the cost of `strcmp`, which depends on word length.

## Build and run

Run it from the folder that contains `Dictionary.txt`:

```bash
gcc AVLDictionary.c -o AVLDictionary
./AVLDictionary
```

The colored output uses `\e` escape codes, which `gcc` accepts. They work in most terminals, including Windows Terminal.

## Known limitations

- **Suggestions can be `(null)`.** If the misspelled word comes before the first word or after the last word in the dictionary, there's no predecessor or successor. The program then passes a `NULL` pointer to `printf("%s")`. That is undefined behaviour in C. With `gcc` on Linux it prints `(null)`, which is what I saw, but it isn't guaranteed everywhere.
- **Four functions are missing a `return` on some path:** `max1`, `search`, `searchForSuc` and `findMax`. The compiler warns about each one. In `findMax`, the branch that recurses never returns the result, which is undefined behaviour. All my tests happened to work, but it can break with different compiler settings.
- **The red color code is typed wrongly.** `"\e\t[0;31m"` has a stray tab between the escape character and `[`, so the terminal may print `[0;31m` as text instead of coloring `INCORRECT` red. It should be `"\e[0;31m"`.
- **`mango` is always accepted.** It's hard-coded as the first word, so it counts as correct even if it isn't in `Dictionary.txt`. If the file can't be opened, the program prints a message and carries on with `mango` as the only word.
- **`Size` isn't the number of words in the tree.** It counts every word read from the file, including duplicates (three lines of `apple` give a size of 3), and it doesn't count the `mango` seed.
- **Matching is exact.** It's case-sensitive (`Apple` is not `apple`, and capital letters sort before lowercase ones), and punctuation stays attached to the word, so `hello,` is treated as a different word from `hello`.
- **Only spaces split the sentence.** Tabs and commas don't.
- **Long words overflow buffers.** A dictionary word of 50 or more characters overflows `buff[50]` in `DictionaryToTree`, because `fscanf("%s")` has no width limit.
- **Sentences are cut at 99 characters** by `fgets(line, 100, ...)`.
- The tree is never freed, and `main` has no `return`.
- Global variables (`last`, `succc`, `preee`, `rootMain`) carry the search state, which makes the code harder to reuse.

## Concepts practiced

- AVL trees: heights, balance factor, rotations
- Working with strings: `strcmp`, `strcpy`, `strtok`, `fgets`
- Reading a file with `fopen` and `fscanf`
- In-order successor and predecessor in a binary search tree
- Using a data structure to build a real tool
