#include <Chess/Piece.hpp>
#include <ResourceManager/ResourceManager.hpp>

namespace Chess {

Piece::Piece() {
    const sf::Texture& tex = ResourceManager::get().getTexture("../resources/chess_pieces.png");
    m_sprite.setTexture(tex);
    m_sprite.setScale(100.0 / (tex.getSize().x / 6), 100.0 / (tex.getSize().y / 2));
    setType(PieceType::WhitePawn);
}
Piece::Piece(PieceType type) : Piece() { setType(type); }

void Piece::setType(PieceType type) {
    if (type == PieceType::Empty) {
        m_sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
        return;
    }
    int x = (int)type % 6;
    int y = (int)type / 6;
    const int size = m_sprite.getTexture()->getSize().x / 6;
    m_sprite.setTextureRect(sf::IntRect(size * x, size * y, size, size));
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_sprite, states);
}
}  // namespace Chess
