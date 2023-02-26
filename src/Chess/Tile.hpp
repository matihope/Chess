#pragma once
#include <Chess/Piece.hpp>
#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>

namespace Chess {
class Tile : public WorldEntity {
    sf::RectangleShape m_shape;
    Piece m_piece;

   public:
    Tile();
    void setColor(sf::Color color);
    void setSize(float size);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPiece(PieceType type);
    void clearPiece();
};
}  // namespace Chess
