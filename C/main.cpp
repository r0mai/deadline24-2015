
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

int score(const field_matrix& field, const building& b, bool garden = false) {
    assert(b.shape >= 0);
    assert(b.rotation >= 0);
    const auto& shape = shapes[b.shape][b.rotation];
    unsigned ox, oy;
    std::tie(ox, oy) = get_origin(shape);

    unsigned fw = field[0].size();
    unsigned fh = field.size();

    unsigned sw = shape[0].size();
    unsigned sh = shape.size();

    if (b.x < ox) {
        return -101;
    }
    if (b.y < oy) {
        return -102;
    }
    if (b.x + (sw - ox - 1) >= fw) {
        return -103;
    }
    if (b.y + (sh - oy - 1) >= fh) {
        return -104;
    }

    int score = 0;
    for (unsigned sx = 0; sx < sw; ++sx) {
        for (unsigned sy = 0; sy < sh; ++sy) {
            if (shape[sy][sx] == ' ') {
                continue;
            }
            switch (field[oy + sy][ox + ox]) {
            case INACCESSIBLE:
                return -105;
            case TREE:
                if (garden) {
                    score += 2;
                } else {
                    score -= 2;
                }
                break;
            case EMPTY:
            default:
                break;
            }
        }
    }
    return score;
}

void do_it() {
    int n, m;
    std::cin >> m >> n;

    field_matrix field(m, std::vector<field_t>(n, EMPTY));

    for (int y = 0; y < m; ++y) {
        std::cin.ignore();
        std::string line;
        std::cin >> line;
        assert(line.size() == n);
        for (int x = 0; x < n; ++x) {
            field[y][x] = char_to_field(line[x]);
        }
    }
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            std::cout << field_to_char(field[y][x]);
        }
        std::cout << std::endl;
    }
    building b;
    b.shape = 0;
    b.rotation = 0;
    for (int y = 0; y < m; ++y) {
        for (int x = 0; x < n; ++x) {
            b.x = x;
            b.y = y;
            std::cout << b.x << " " << b.y << " ";
            std::cout << score(field, b) << std::endl;
        }
    }
}

int main() {
    int t;
    std::cin >> t;
    for (int i = 0; i < t; ++i) {
        do_it();
    }
//    for (const auto& sp : shapes) {
//        for (const auto& s : sp) {
//            std::cout << "-------------" << std::endl;
//            print_shape(s);
//        }
//    }
}
