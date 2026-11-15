# Problem 206 – Concealed Square

[Problem on Project Euler](https://projecteuler.net/problem=206)

**Task:** Find the unique positive integer whose square has the form `1_2_3_4_5_6_7_8_9_0`, where each `_` is a single digit.

**Info** Since it is not planned to show the solution to a Project Euler problem above 100, only the approach is shown

## Approach

1. **Bounds.** The square lies between `1020304050607080900` and `1929394959697989990`.
   So the number lies between √1020304050607080900 ≈ 1 010 101 010 and √1929394959697989990 ≈ 1 389 026 623.
   That leaves about 380 million candidates instead of searching blindly.

2. **The last digit.** The square ends in `0`, so the number itself must end in `0`.
   Only every 10th candidate has to be checked, which leaves about 38 million.

3. **Checking a candidate.** The squares fit into `uint64_t` (max. ≈ 1.93 · 10¹⁸).
   The last two digits are always `00`, so the check divides by 100 first and then compares every second digit from the right with 9, 8, 7, …, 1, dividing by 100 each step.
   It stops at the first wrong digit, so most candidates are rejected after one or two steps.

## Possible improvement

If the number ends in `0`, its square ends in `00`, and the digit before that must be `9`.
That only works if the number ends in `30` or `70`, which removes another 80 % of the candidates.

## Build

```bash
g++ -std=c++17 -O2 main.cpp -o concealed_square
./concealed_square
```