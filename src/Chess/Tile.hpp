#pragma once
#include <Chess/Piece.hpp>
#include <Chess/Square.hpp>
#include <CollisionShape/CollisionShape.hpp>
#include <GUI/Label.hpp>
#include <SFML/Graphics.hpp>
#include <WorldEntity/WorldEntity.hpp>

class ChessScene;

namespace Chess {
class Tile : public WorldEntity {
    bool m_flipped;
    sf::RectangleShape m_shape;
    Piece m_piece;
    RectCollision m_collision_shape;
    Square m_square;
    GUI::Label m_file_label;
    GUI::Label m_rank_label;
    void setLabel();

   public:
    Tile();
    Tile(Square sqaure);
    void update(const float dt) override;
    void setColor(sf::Color color);
    void setSize(float size);
    void setSquare(Square square);
    Square getSquare();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void setPiece(PieceType type);
    void clearPiece();
    void setFlipped(bool flipped);
};
}  // namespace Chess
