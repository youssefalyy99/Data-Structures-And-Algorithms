# Project 1: Expression Evaluator

A command-line calculator written in C. You type an arithmetic expression in normal (infix) notation, such as `( 2 + 3 ) * 4`. The program converts it to **postfix** notation, prints it, evaluates it, and prints the result.

The whole project is built on one data structure: a **stack implemented with a linked list**.

## Files

| File | What it is |
|------|------------|
| `ExpressionEvaluation.c` | The whole program. |

## What it supports

| Feature | Details |
|---------|---------|
| Operators | `+` `-` `*` `/` `%` `^` (power) |
| Parentheses | `(` and `)` |
| Numbers | Integers and decimals (`2.5`), including negative numbers written as one token (`-3`) |
| Precedence | `^` first, then `*` `/` `%`, then `+` `-` |

Every number, operator and parenthesis is separated by a space, for example `3 + 4 * 2`.

## Example runs

```
>> Input (Infix) : 3 + 4 * 2
Final Postfix Expression : 3.00 4.00 2.00 * +
Final Value : 11.00
```

```
>> Input (Infix) : ( 2 + 3 ) * ( 4 - 1 ) ^ 2
Final Postfix Expression : 2.00 3.00 + 4.00 1.00 - 2.00 ^ *
Final Value : 45.00
```

```
>> Input (Infix) : 10 / 4 - 1
Final Postfix Expression : 10.00 4.00 / 1.00 -
Final Value : 1.50
```

Results are printed with two decimal places.

## How it works

The program has three parts, matching the comments in the code.

### Part 1: Stack using a linked list

```c
typedef struct Node {
    float data;
    struct Node* next;
} Node;

typedef struct {
    Node *top;      // the last node (where push and pop happen)
    Node *start;    // the first node
} Stack;
```

| Function | What it does | Time |
|----------|--------------|------|
| `initialize()` | Creates an empty stack. | O(1) |
| `newnode()` | Allocates one node. | O(1) |
| `push(s, value)` | Adds a value on top. | O(1) |
| `pop(s)` | Removes and returns the top value. | O(n) |
| `peek(s)` | Returns the top value without removing it. | O(1) |
| `isEmpty(s)` | Returns 1 if the stack has no elements. | O(1) |
| `display(s)` | Prints the stack from bottom to top. | O(n) |

`pop` is O(n) because the list is singly linked: to find the node before the top, it walks from `start`.

### Part 2: Infix to postfix

**Postfix** (also called reverse Polish notation) puts each operator after its operands, so no parentheses or precedence rules are needed when evaluating: `3 + 4 * 2` becomes `3 4 2 * +`.

The program uses two stacks: `final` for the output, and `buffer` for operators that are waiting.

1. A **number** goes straight to `final`.
2. An **operator** is compared with the operator on top of `buffer`. If it has higher priority, it's pushed. Otherwise, operators on the buffer with equal or higher priority are moved to `final` first, then it's pushed.
3. A `)` moves operators from `buffer` to `final` until the matching `(` is found, then removes the `(`.
4. At the end, everything left in `buffer` is moved to `final`.

Priorities from `prior()`: `^` is 3, `*` `/` `%` are 2, `+` `-` are 1. Equal priorities are handled left to right.

Trace of `3 + 4 * 2`:

| Token | Output (`final`) | Waiting (`buffer`) |
|-------|------------------|--------------------|
| `3` | 3 | |
| `+` | 3 | + |
| `4` | 3 4 | + |
| `*` | 3 4 | + * |
| `2` | 3 4 2 | + * |
| end | 3 4 2 * + | |

### Part 3: Postfix evaluation

Scan the postfix expression from left to right with a stack:

1. A **number** is pushed.
2. An **operator** pops two numbers (the second one popped is the left operand), applies the operator, and pushes the result.
3. The single value left at the end is the answer.

For `3 4 2 * +`: push 3, 4, 2. Then `*` gives 4 * 2 = 8, and the stack is `3 8`. Then `+` gives 11.

`%` converts both numbers to integers first, and `^` uses `pow()` from `<math.h>`.

## Limitations

- The program assumes a well-formed expression: tokens separated by spaces, balanced parentheses, and no `%` by zero. Invalid input isn't checked.
- Operators are stored as character codes in the same stack as numbers, so the numbers 37, 40, 41, 42, 43, 45, 47 and 94 are read as operators.
- `prior()` has no value for `(`, which can give wrong answers when the program is compiled with optimization.

## Concepts practiced

- Stack (LIFO) built on a singly linked list
- Infix and postfix notation
- Operator precedence and parentheses
- Using a stack to parse and evaluate expressions
- String tokenizing with `strtok`, and `atof`
