#pragma once

namespace Chess {
struct Position {
  char file;
  unsigned int rank;

  Position() : Position('A', 1) {}

  Position(char file, unsigned int rank) : file(file), rank(rank) {}
};
}  // namespace Chess
