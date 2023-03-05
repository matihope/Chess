#pragma once

namespace Chess {
struct Square {
    char file;
    int rank;
    Square(char file = 'A', int rank = 1) : file(file), rank(rank) {}
    bool operator ==(const Square &b) const {
        return b.file == file && b.rank == rank;
    }
};
}  // namespace Chess
