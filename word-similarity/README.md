# Word Similarity

A small experiment from before I used AI tools: can a program "know" which groceries are similar, if every word is just a point in 2D space?

## Idea

Every grocery gets a hand-picked 2D vector, so that similar foods lie close together:

| Grocery | Vector |
|---|---|
| Citron | (-0.30, 0.42) |
| Orange | (0.10, 0.30) |
| Bread | (0.15, -0.30) |
| Pasta | (0.20, -0.25) |
| Cheese | (-0.20, -0.45) |
| Milk | (0.05, -0.15) |
| Eggs | (0.05, -0.05) |
| Tomatoes | (0.30, 0.10) |

The program compares every pair and prints how similar they are.

This is the basic principle behind **word embeddings** in modern language models, only with 2 hand-chosen dimensions instead of hundreds learned from data.

## Similarity measure

Similarity is the inverse of the Manhattan distance:

```
similarity = 1 / (|x1 - x2| + |y1 - y2|)
```

| Similarity | Output |
|---|---|
| ≤ 1 | are not similar |
| ≤ 1.8 | are a little bit similar |
| ≤ 5 | are similar |
| > 5 | are very similar |

I also tried other measures, among them one based on the angle between the vectors and their difference in length. The Manhattan distance gave the most sensible results for this data.

## Build

```bash
g++ -std=c++17 main.cpp -o word_similarity
./word_similarity
```