#pragma once

namespace Chess {
struct Square {
    char file;
    int rank;
    Square(char file = 'A', int rank = 1) : file(file), rank(rank) {}
};
}  // namespace Chess
