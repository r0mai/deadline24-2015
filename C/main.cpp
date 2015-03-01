
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

struct construction {
    building house;
    building garden;
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
                score += 2;
                break;
            case EMPTY:
            default:
                break;
            }
        }
    }
    return score;
}

bool has_common_side(const building& a, const building& b) {
    const auto& ashape = shapes[a.shape][a.rotation];
    unsigned aox, aoy;
    std::tie(aox, aoy) = get_origin(ashape);

    const auto& bshape = shapes[b.shape][b.rotation];
    unsigned box, boy;
    std::tie(box, boy) = get_origin(bshape);

    char_matrix field(220, std::vector<char>(220, ' '));

    unsigned asw = ashape[0].size();
    unsigned ash = ashape.size();

    unsigned bsw = bshape[0].size();
    unsigned bsh = bshape.size();

    for (unsigned asx = 0; asx < asw; ++asx) {
        for (unsigned asy = 0; asy < ash; ++asy) {
            if (ashape[asy][asx] != ' ') {
                field[aoy + asy][aox + asx] = '1';
            }
        }
    }
    for (unsigned bsx = 0; bsx < bsw; ++bsx) {
        for (unsigned bsy = 0; bsy < bsh; ++bsy) {
            if (ashape[bsy][bsx] != ' ') {
                if (field[boy + bsy][box + bsx] == '1') {
                    assert(false && "overlap");
                }
                field[boy + bsy][box + bsx] = '2';
                if (boy + bsy > 0 && field[boy + bsy - 1][box + bsx] == '1') {
                    return true;
                }
                if (box + bsx > 0 && field[boy + bsy][box + bsx - 1] == '1') {
                    return true;
                }
                if (field[boy + bsy + 1][box + bsx] == '1') {
                    return true;
                }
                if (field[boy + bsy][box + bsx + 1] == '1') {
                    return true;
                }
            }
        }
    }
    return false;
}

int score(const field_t& field, const construction& c) {
    int house_score = score(field, c.house);
    int garden_score = score(field, c.garden);

    if (house_score < 0 || garden_score < 0) {
        return -101;
    }

    if (!has_common_side(c.house, c.garden)) {
        return -102;
    }

    return -house_score + garden_score;
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
