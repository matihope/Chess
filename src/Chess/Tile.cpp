#include <Chess/Tile.hpp>

namespace Chess {
Tile::Tile() {
    m_shape = sf::RectangleShape();
    m_piece.setType(Chess::PieceType::Empty);
}

void Tile::setColor(sf::Color color) { m_shape.setFillColor(color); }

void Tile::setSize(float size) { m_shape.setSize(sf::Vector2f(size, size)); }

void Tile::setPiece(PieceType type) { m_piece.setType(type); }
void Tile::clearPiece() { m_piece.setType(PieceType::Empty); }

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_shape, states);
    target.draw(m_piece, states);
}

}  // namespace Chess
