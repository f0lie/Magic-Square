#ifndef MAGIC_SQUARE_MAGIC_SQUARE_H
#define MAGIC_SQUARE_MAGIC_SQUARE_H

#include <vector>

typedef std::vector<int> slice_t;
typedef std::vector<slice_t> board_t;
typedef std::pair<const int, const int> point_t;

class Magic_Square {
public:
    explicit Magic_Square(const int size);
    void print();

    slice_t sum_row();
    slice_t sum_col();
    slice_t sum_diag();

    void rotate();

private:
    const int order;
    board_t board;

    void construct();
    bool is_empty(const point_t);

    void write(const point_t point, const int element);
    point_t move(const point_t point);
    point_t wrap(point_t point);

    slice_t get_row(const int row);
    slice_t get_col(const int col);
    slice_t get_diag_left_right();
    slice_t get_diag_right_left();

};

#endif //MAGIC_SQUARE_MAGIC_SQUARE_H
