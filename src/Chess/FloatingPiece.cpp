#include <Chess/FloatingPiece.hpp>

namespace Chess {
void FloatingPiece::setPiece(Piece piece, const sf::Texture& texture, sf::IntRect rect) {
    // m_piece = piece;
    // m_sprite.setTexture(texture);
    // m_sprite.setTextureRect(rect);
}

void FloatingPiece::update(float dt) { WorldEntity::update(dt); }
}  // namespace Chess
