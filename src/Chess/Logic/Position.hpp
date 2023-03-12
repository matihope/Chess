#pragma once
#include <ostream>

namespace Chess {
struct Position {
  char file;
  unsigned int rank;

  Position() : Position('A', 1) {}

  Position(char file, unsigned int rank) : file(file), rank(rank) {}
  friend std::ostream &operator<<( std::ostream &output, const Position &p ) {
    output << "Pos: " << p.file << p.rank;
    return output;
  }
};
}  // namespace Chess
