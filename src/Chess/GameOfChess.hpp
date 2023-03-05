#pragma once
#include <Chess/Tile.hpp>
#include <Chess/Piece.hpp>
#include <Chess/Square.hpp>
#include <array>
#include <memory>
#include <vector>

namespace Chess {
class GameOfChess {
   private:
    std::array<PieceType, 64> m_board;
    PieceType& getMutPieceAt(char file, int rank);
    PieceType& getMutPieceAt(Chess::Square pos);

   public:
    GameOfChess();
    void reset();
    const PieceType& getPieceAt(char file, int rank);
    const PieceType& getPieceAt(Chess::Square pos);
    std::vector<Chess::Square> getAvailableMovesAt(Chess::Square pos);
};
}  // namespace Chess
