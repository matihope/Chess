#pragma once
#include <ostream>

namespace Chess {
struct Position {
  char file;
  int rank;

  Position() : Position('A', 1) {}

  Position(char file, int rank) : file(file), rank(rank) {}

  friend bool operator==(const Position &lhs, const Position &rhs) {
    return lhs.file == rhs.file and lhs.rank == rhs.rank;
  }
};
}  // namespace Chess
