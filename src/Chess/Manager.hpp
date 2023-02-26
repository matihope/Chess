#pragma once
#include <Chess/Piece.hpp>
#include <array>
#include <memory>

namespace Chess {
class Manager {
   private:
    std::array<PieceType, 64> m_board;
    PieceType& getMutPieceAt(char file, int rank);

   public:
    Manager();
    void reset();
    const PieceType& getPieceAt(char file, int rank);
};
}  // namespace Chess
