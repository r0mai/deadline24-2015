
#include <vector>
#include <cassert>
#include <iostream>

enum field_t {
    TREE, EMPTY, INACCESSIBLE
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

template<class T>
using matrix = std::vector<std::vector<T>>;

using field_matrix = matrix<field_t>;


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
}
