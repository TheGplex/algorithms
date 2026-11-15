# Problem 59 – XOR Decryption

[Problem on Project Euler](https://projecteuler.net/problem=59)

**Task:** A text was encrypted with XOR using a key of three lowercase letters that repeats over the whole text. Find the key, decrypt the text and sum up the ASCII values of the plain text.

## Approach

1. **Brute force over all keys.** Three lowercase letters give 26³ = 17 576 possible keys, few enough to try them all.
2. **Decrypting.** Character `i` of the text is XORed with key character `i % 3`. XOR is its own inverse, so the same operation encrypts and decrypts.
3. **Recognising the right key.** For every key, the program counts how many decrypted characters are letters (A–Z, a–z). English text consists mostly of letters, so the right key gives a much higher ratio than random keys. A key with at least 73.5 % letters is accepted; the search stops at the first match.
4. **Result.** The program prints the plain text, the key and the sum of the ASCII values.

## Build

```bash
g++ -std=c++17 -O2 main.cpp -o xor_decryption
./xor_decryption
```