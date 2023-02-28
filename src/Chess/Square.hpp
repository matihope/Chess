#pragma once

namespace Chess {
struct Square {
    char file;
    int rank;
    Square(char file, int rank) : file(file), rank(rank) {}
};
}  // namespace Chess
