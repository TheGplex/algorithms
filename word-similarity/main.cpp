#include <iostream>

#define CITRON 0
#define ORANGE 1
#define BREAD 2
#define PASTA 3
#define CHEESE 4
#define MILK 5
#define EGGS 6
#define TOMATOES 7

#define SAMPLE_SIZE 8


class vector2 {
public:
    float x, y;

    vector2() = default;

    void init(const float value[2]) {x=value[0]; y=value[1];}

    float calc(const vector2 v2) { // best working
        const float xDiff = x >= v2.x ? x - v2.x : v2.x - x;
        const float yDiff = y >= v2.y ? y - v2.y : v2.y - y;

        return 1 / (xDiff + yDiff);
    }

};

std::string similarity(vector2 v1, vector2 v2) {
    const float sim = v1.calc(v2);
    std::string word = " ";

    if (sim <= 1) {
        word = " are not ";
    } else if (sim > 1 && sim <= 1.8) {
        word = " are a little bit ";
    } else if (sim > 1.8 && sim <= 5) {
        word = " are ";
    } else if (sim > 5) {
        word = " are very ";
    }

    return word;
}

int main() {
    const float vectValues[SAMPLE_SIZE][2] = {
        {-0.3, 0.42},
        {0.1, 0.3},
        {0.15, -0.3},
        {0.2, -0.25},
        {-0.2, -0.45},
        {0.05, -0.15},
        {0.05, -0.05},
        {0.3, 0.1}
    };

    const std::string names[SAMPLE_SIZE] = {
        "Citron", "Orange", "Bread", "Pasta",
        "Cheese", "Milk", "Eggs", "Tomatoes"
    };

    vector2 v[SAMPLE_SIZE];

    for (int i = 0; i < SAMPLE_SIZE; i++) {
        v[i].init(vectValues[i]);
    }

    for (int i = 0; i < SAMPLE_SIZE - 1; i++) {
        for (int j = i + 1; j < SAMPLE_SIZE; j++) {
            const std::string word = similarity(v[i], v[j]);
            std::cout << names[i] << " and " << names[j] << word << "similar (" << v[i].calc(v[j]) << ")" << std::endl;
        }
    }

    return 0;
}
