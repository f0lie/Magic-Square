#ifndef MAGIC_SQUARE_MAIN_H
#define MAGIC_SQUARE_MAIN_H

#include <vector>
#include <utility>
#include <exception>
#include <algorithm>

typedef std::vector<int> slice_t;
typedef std::pair<int, int> point_t;
typedef std::vector<slice_t> board_t;

class Magic_Square {
public:
    Magic_Square(const int size);
    virtual ~Magic_Square();
    void print();

    slice_t sum_row();
    slice_t sum_col();
    slice_t sum_diag();

    void rotate();

private:
    board_t board;
    const int order;

    void construct();
    bool is_empty(point_t);

    void write(point_t point, int element);
    point_t move(point_t point);
    point_t wrap(point_t point);

    slice_t get_row(const int row);
    slice_t get_col(const int col);
    slice_t get_diag_left_right();
    slice_t get_diag_right_left();

};


#endif //MAGIC_SQUARE_MAIN_H
