#pragma once
#include <WorldEntity/WorldEntity.hpp>

namespace Chess {

enum class PieceType {
    WhiteKing,
    WhiteQueen,
    WhiteBishop,
    WhiteKnight,
    WhiteRook,
    WhitePawn,
    BlackKing,
    BlackQueen,
    BlackBishop,
    BlackKnight,
    BlackRook,
    BlackPawn,
    Empty
};

class Piece : public WorldEntity {
   private:
    sf::Sprite m_sprite;
    PieceType m_type;

   public:
    Piece();
    Piece(PieceType);
    void setType(PieceType);
    const PieceType& getType();
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};
}  // namespace Chess
