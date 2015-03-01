#pragma once

#include <vector>
#include <array>
#include <tuple>
#include <iostream>

template<class T>
using matrix = std::vector<std::vector<T>>;

using char_matrix = matrix<char>;

void print_shape(const char_matrix& s) {
    for (const auto& l : s) {
        for (auto c : l) {
            std::cout << c;
        }
        std::cout << std::endl;
    }
}

const char_matrix shape_a = {
    {'O', ' '},
    {'X', 'X'},
    {'X', 'X'},
    {'X', 'X'}
};

const char_matrix shape_b = {
    {'O', 'X', 'X'},
    {'X', 'X', ' '},
    {'X', ' ', ' '}
};

const char_matrix shape_c = {
    {' ', 'O', ' '},
    {'X', 'X', ' '},
    {'X', 'X', 'X'}
};

const char_matrix shape_d = {
    {' ', 'O'},
    {' ', 'X'},
    {'X', 'X'},
    {'X', 'X'}
};

const char_matrix shape_e = {
    {'O', ' ', ' '},
    {'X', ' ', ' '},
    {'X', ' ', ' '},
    {'X', 'X', 'X'}
};

const char_matrix shape_f = {
    {'O'},
    {'X'},
    {'X'},
    {'X'},
    {'X'},
    {'X'}
};

const char_matrix shape_g = {
    {'O', 'X', 'X', 'X'},
    {'X', ' ', ' ', 'X'}
};

const char_matrix shape_h = {
    {'O', 'X', ' '},
    {'X', ' ', ' '},
    {'X', 'X', 'X'}
};

const char_matrix shape_i = {
    {'O', 'X', ' '},
    {' ', 'X', ' '},
    {' ', 'X', ' '},
    {' ', 'X', 'X'}
};

const char_matrix shape_j = {
    {'O', ' ', 'X'},
    {'X', 'X', 'X'},
    {'X', ' ', ' '}
};

char_matrix rotate(const char_matrix& m) {
    unsigned w = m[0].size();
    unsigned h = m.size();
    char_matrix res(w, std::vector<char>(h, ' '));

    for (unsigned x = 0; x < w; ++x) {
        for (unsigned y = 0; y < h; ++y) {
            unsigned nx = h - 1 - y;
            unsigned ny = x;
            res.at(ny).at(nx) = m[y][x];
        }
    }
    return res;
}

using shapes_t = std::array<std::array<char_matrix, 4>, 10>;

shapes_t generate_shapes() {
    shapes_t res;
    res[0][0] = shape_a;
    res[1][0] = shape_b;
    res[2][0] = shape_c;
    res[3][0] = shape_d;
    res[4][0] = shape_e;
    res[5][0] = shape_f;
    res[6][0] = shape_g;
    res[7][0] = shape_h;
    res[8][0] = shape_i;
    res[9][0] = shape_j;
    for (int i = 0; i < 10; ++i) {
        for (int r = 1; r < 4; ++r) {
            res[i][r] = rotate(res[i][r-1]);
        }
    }
    return res;
}

const shapes_t shapes = generate_shapes();

std::tuple<unsigned, unsigned> get_origin(const char_matrix& s) {
    for (unsigned y = 0; y < s.size(); ++y) {
        for (unsigned x = 0; x < s[y].size(); ++x) {
            if (s[y][x] == 'O') {
                return std::make_tuple(x, y);
            }
        }
    }
    assert(false);
    return std::make_tuple(0, 0);
}
