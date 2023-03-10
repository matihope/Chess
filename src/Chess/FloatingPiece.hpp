#pragma once
#include <Chess/Piece.hpp>
#include <WorldEntity/WorldEntity.hpp>

namespace Chess {
class FloatingPiece : public WorldEntity {
    // Piece m_piece;
    // sf::Sprite m_sprite;

   public:
    // ~FloatingPiece() {}
    void setPiece(Piece piece, const sf::Texture& texture, sf::IntRect rect);
    void update(const float dt) override;
};
}  // namespace Chess
