#include <iostream>
#include <memory>

#include "main.h"
#include "magic_square.h"

using std::cout;
using std::endl;
using std::cin;
using std::vector;

void print(slice_t sum);

int main() {
    cout << "Enter the size of the magic square" << endl;

    int order = 0;

    std::unique_ptr<Magic_Square> square(new Magic_Square(3));

    while (true) {
        try {
            cin >> order;
            square.reset(new Magic_Square(order));
            break;
        } catch (std::logic_error e) {
            cout << e.what() << endl;
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

        cout << endl << endl;
    }

    return 0;
}

void print(slice_t sum) {
    for (slice_t::const_iterator slice_it = sum.begin(); slice_it != sum.end(); slice_it++) {
        cout << *slice_it << " ";
    }
    cout << endl;
}

