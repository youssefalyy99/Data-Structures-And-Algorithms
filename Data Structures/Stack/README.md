# Stack

A stack is a collection that follows **LIFO** (Last In, First Out): the last item pushed is the first one popped. Think of a pile of plates.

This folder has an array-based stack in C and two programs that use it.

## Files

| File | What it is |
|------|------------|
| `stack.h` | The stack, with the struct and all functions. The two programs include this file. |
| `stack.c` | A standalone copy of the same stack with an empty `main`. Not used by the programs. |
| `InfixToPostfix.c` | Converts an infix expression (`2+3*4`) to postfix (`2 3 4 * +`). |
| `PostfixExpressions.c` | Evaluates a postfix expression (`234*+`) and prints the result. |

## How the stack works

```c
typedef struct {
    int arr[100];   // storage, fixed capacity of 100
    int top;        // index of the top element, -1 when empty
} stack;
```

| Function | What it does | Time |
|----------|--------------|------|
| `initialize()` | Allocates a stack and sets `top = -1` | O(1) |
| `push(s, value)` | Adds a value on top | O(1) |
| `pop(s)` | Removes and returns the top value | O(1) |
| `peek(s)` | Returns the top value without removing it | O(1) |
| `isEmpty(s)` | Returns 1 if the stack has no elements | O(1) |
| `isFull(s)` | Returns 1 if the stack holds 100 elements | O(1) |

Space is O(n), with a fixed maximum of 100 elements.

## Programs

### Infix to Postfix

Reads an infix expression with no spaces, such as `2+3*4`, and prints the postfix form.

How it works:
1. Digits go straight to the output.
2. Operators go on a stack. Before pushing, operators on the stack with equal or higher priority are moved to the output first.
3. `*`, `/`, `%` have higher priority than `+`, `-`.
4. On `)`, operators are popped to the output until the matching `(` is found.
5. At the end, everything left on the stack is moved to the output.

### Postfix Evaluation

Reads a postfix expression with no spaces, such as `234*+`, and prints the result.

How it works:
1. Scan left to right.
2. If the character is a digit, push it.
3. If it is an operator, pop two values, apply the operator, and push the result.
4. The final value left on the stack is the answer.

Supported operators: `+`, `-`, `*`, `/`.

## Build and run

Compile from inside this folder, because the programs use `#include "stack.h"`:

```bash
gcc InfixToPostfix.c -o InfixToPostfix
gcc PostfixExpressions.c -o PostfixExpressions
```

Do not compile `stack.c` together with the other files, since each has its own `main`.

## Known limitations

- Only single-digit numbers are supported.
- Expressions must not contain spaces.
- There are no overflow or underflow checks: pushing more than 100 elements, or popping an empty stack, is undefined behaviour.
- `stack.h` has no include guard, so it should be included only once per file.
- `Infix to Postfix` only recognises `+ - * / % ( )`, and `Postfix Evaluation` has no `%`.

## Concepts practiced

- Array-based stack implementation
- Operator precedence
- Using a stack for parsing and evaluating expressions
