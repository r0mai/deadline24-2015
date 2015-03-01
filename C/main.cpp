
#include <vector>
#include <cassert>
#include <iostream>

#include "shapes.hpp"

enum field_t {
    TREE, EMPTY, INACCESSIBLE
};

using field_matrix = matrix<field_t>;

// garden or house
struct building {
    int shape = -1;
    int rotation = -1;
    int x = -1;
    int y = -1;
};

field_t char_to_field(char ch) {
    switch (ch) {
        case 'X': return TREE;
        case '#': return INACCESSIBLE;
        case '.': return EMPTY;
        default: assert(false); return EMPTY;
    }
}

char field_to_char(field_t f) {
    switch (f) {
        case TREE: return 'X';
        case INACCESSIBLE: return '#';
        case EMPTY: return '.';
        default: assert(false); return '?';
    }
}

int score(const field_matrix& field, const building& b) {

}

void do_it() {
    int n, m;
    std::cin >> m >> n;

    field_matrix field(n, std::vector<field_t>(m, EMPTY));

    for (int y = 0; y < m; ++y) {
        std::cin.ignore();
        std::string line;
        std::cin >> line;
        assert(line.size() == n);
        for (int x = 0; x < n; ++x) {
            field[x][y] = char_to_field(line[x]);
        }
    }
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            std::cout << field_to_char(field[x][y]);
        }
        std::cout << std::endl;
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        do_it();
    }
    for (const auto& sp : shapes) {
        for (const auto& s : sp) {
            std::cout << "-------------" << std::endl;
            print_shape(s);
        }
    }
}
