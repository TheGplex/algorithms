# Truth Table

A small C program that computes the truth table of a logic expression with four inputs (`a`, `b`, `c`, `d`). I wrote it to check my solutions for digital electronics exercises at school.

## How it works

The expression is entered in three parts, each combining two operands with one operator:

```
x = (a !& !b)        two of the inputs
y = !(!c ^ d)        the other two inputs
Q = !(x | y)         combines x and y
```

Supported operators:

| Input | Operation |
|---|---|
| `&` | AND |
| `\|` | OR |
| `^` | XOR |
| `!&`, `!\|`, `!^` | NAND, NOR, XNOR |
| `!a` | NOT on a single input |
| `!( … )` | NOT on a whole part |

The program evaluates `x`, `y` and `Q` for all 16 input combinations and prints the 16 values of `Q`, in the order `abcd = 0000, 0001, …, 1111`.

### Implementation

- Inputs `a` to `d` are stored as the first four rows of a 7 × 16 table, holding all combinations. `x`, `y` and `Q` fill the remaining three rows.
- The six operators are ordered in an enum so that the inverted operator is always 3 positions after the normal one (`OR → NOR`, `AND → NAND`, `XOR → XNOR`). A leading `!` simply adds 3.
- Input is checked against a list of allowed characters before evaluating.

## Limitations

- Exactly four inputs, two per part, and one operator per part. Longer expressions have to be split by hand first, as described in the program's help text.
- There is no general parser for arbitrary expressions.

## Build

```bash
gcc -std=c17 main.c -o truth_table
./boolean_solver
```