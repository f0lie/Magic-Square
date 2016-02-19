#include <iostream>

#include "main.h"
#include "magic_square.h"

using std::cout;
using std::cin;
using std::vector;

void print(const slice_t sum);

int main() {
    cout << "Enter the size of the magic square \n";

    int order = 0;

    std::unique_ptr<Magic_Square> square(new Magic_Square(3));

    while (true) {
        try {
            cin >> order;
            square.reset(new Magic_Square(order));
            break;
        } catch (std::logic_error e) {
            cout << e.what() << "\n";
        }
    }

    for (int i = 0; i < 3; i++) {
        square->print();
        cout << "Rows sum: ";
        print(square->sum_row());
        cout << "Cols sum: ";
        print(square->sum_col());
        cout << "Diagonals sum: ";
        print(square->sum_diag());

        square->rotate();

        cout << "\n\n";
    }

    return 0;
}

void print(const slice_t sum) {
    for (auto element : sum) {
        cout << element << " ";
    }
    cout << "\n";
}

