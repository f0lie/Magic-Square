#include <iostream>
#include <utility>
#include <algorithm>

#include "magic_square.h"
#include "main.h"

Magic_Square::Magic_Square(const int size) : order(size), board(order, slice_t(order)) {
    if (order % 2 == 0) {
        throw std::logic_error("Order cannot be even.");
    }
    if (order > 15) {
        throw std::logic_error("Order cannot be above 15.");
    }
    if (order < 3) {
        throw std::logic_error("Order cannot be below 3.");
    }

    construct();
}

void Magic_Square::print() {
    for (slice_t slice : board) {
        for (auto element : slice) {
            if (element < 10) {
                std::cout << "  " << element << " ";
            } else if(element < 100) {
                std::cout << " " << element << " ";
            } else {
                std::cout << element << " ";
            }
        }
        std::cout << "\n";
    }
}

// Checks if all of the sums of the array are equal
slice_t check_sum(const slice_t sums) {
    for (unsigned int i = 0; i < sums.size() - 1; i++) {
        if (sums[i] != sums[i + 1]) {
            throw std::logic_error("Not a magic square!");
        }
    }
    return sums;
}

// Get the sum of an array
int get_sum(const slice_t slice) {
    int sum = 0;

    for (auto element : slice) {
        sum += element;
    }

    return sum;
}

slice_t Magic_Square::get_row(const int row) {
    return board[row];
}

slice_t Magic_Square::sum_row() {
    slice_t sums;
    for (int i = 0; i != order; i++) {
        sums.push_back(get_sum(get_row(i)));
    }
    return check_sum(sums);
}

slice_t Magic_Square::get_col(const int col) {
    slice_t out_col;
    for (slice_t slice : board) {
        out_col.push_back((slice)[col]);
    }
    return out_col;
}

slice_t Magic_Square::sum_col() {
    slice_t sums;
    for (int i = 0; i != order; i++) {
        sums.push_back(get_sum(get_col(i)));
    }
    return check_sum(sums);
}

slice_t Magic_Square::get_diag_left_right() {
    slice_t diag;
    for (int row = 0, col = 0; row != order || col != order; row++, col++) {
        diag.push_back(board[row][col]);
    }
    return diag;
}

slice_t Magic_Square::get_diag_right_left() {
    slice_t diag;
    for (int row = order - 1, col = order - 1; row >= 0 || col >= 0; row--, col--) {
        diag.push_back(board[row][col]);
    }
    return diag;
}

slice_t Magic_Square::sum_diag() {
    slice_t sums;
    sums.push_back(get_sum(get_diag_left_right()));
    sums.push_back(get_sum(get_diag_right_left()));
    return sums;
}

// Generates the magic square
void Magic_Square::construct() {
    // Start in middle top of the square
    std::unique_ptr<point_t> point_ptr(new point_t(0, order / 2));

    for (int i = 1; i <= order*order; i++) {
        write(*point_ptr, i);
        point_ptr.reset(new point_t(move(*point_ptr)));
    }
}

// Checks if the point hasn't been write in yet
bool Magic_Square::is_empty(const point_t point) {
    return board[point.first][point.second] == 0;
}

void Magic_Square::write(const point_t point, const int element) {
    if (element < 0) {
        throw std::logic_error("Cannot write negative numbers to board!");
    }

    board[point.first][point.second] = element;
}

// Move in according to the magic square pattern
point_t Magic_Square::move(const point_t point) {
    // Move new point up right.
    std::unique_ptr<point_t> point_ptr(new point_t(point.first - 1, point.second + 1));

    point_ptr.reset(new point_t(wrap(*point_ptr)));

    // If point is occupied then move point one down.
    if (!is_empty(*point_ptr)) {
        // The (row + 2, col - 1) is to negate the first move.
        // So the result is (row + 1, col), below the original position.
        point_ptr.reset(new point_t(point_ptr->first + 2, point_ptr->second - 1));
        point_ptr.reset(new point_t(wrap(*point_ptr)));
    }

    return *point_ptr;
}

// Move the point if it is outside of the bounds of the square
point_t Magic_Square::wrap(const point_t point) {
    int coord_x = point.first;
    int coord_y = point.second;

    // If coord_x is beyond the right edge, then move to left edge
    if (coord_x > order - 1) {
        coord_x -= order;
        // If coord_x is beyond the left edge, then move to right edge
    } else if (coord_x < 0) {
        coord_x += order;
    }

    //Same logic as above
    if (coord_y > order - 1) {
        coord_y -= order;
    } else if (coord_y < 0) {
        coord_y += order;
    }

    return point_t(coord_x, coord_y);
}

// Rotate the magic square to generate the other cases
void Magic_Square::rotate() {
    // Transpose matrix
    for (int i = 0; i != order - 1; i++) {
        for (int j = i + 1; j != order; j++) {
            std::swap(board[i][j], board[j][i]);
        }
    }

    // Flip rows
    for (int i = 0; i != order/2; i++) {
        swap(board[i], board[order-1-i]);
    }
}