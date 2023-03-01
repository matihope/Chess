#include "Tile.hpp"

#include <Chess/Tile.hpp>
#include <Game/Game.hpp>
#include <Scene/ChessScene.hpp>

namespace Chess {
Tile::Tile() : m_collision_shape(RectCollision(this)) {
    m_shape = sf::RectangleShape();
    m_piece.setType(Chess::PieceType::Empty);

    m_flipped = false;
    m_rank_label.setFont(Game::get().getFont());
    m_file_label.setFont(Game::get().getFont());
    m_rank_label.setTextSize(20);
    m_file_label.setTextSize(20);
    m_rank_label.setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::BOTTOM);
    m_file_label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);
}

Tile::Tile(Square square) : Tile::Tile() { setSquare(square); }

void Tile::setColor(sf::Color color) { m_shape.setFillColor(color); }

void Tile::setSize(float size) {
    m_collision_shape.setSize(size, size);
    m_shape.setSize(sf::Vector2f(size, size));
    uint buffer = 3;

    m_rank_label.setPosition(sf::Vector2f(buffer, size - buffer));
    m_file_label.setPosition(sf::Vector2f(size - buffer, buffer));
}

void Tile::setPiece(PieceType type) { m_piece.setType(type); }
void Tile::clearPiece() { m_piece.setType(PieceType::Empty); }

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(m_shape, states);
    target.draw(m_piece, states);
    target.draw(m_file_label, states);
    target.draw(m_rank_label, states);
#if (DEBUG)
    target.draw(m_collision_shape, states);
#endif
}

void Tile::update(const float dt) {
    sf::Vector2f mousePos = Game::get().getMousePos();
    if (m_collision_shape.contains(mousePos)) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            queueFree();
        }
    }
}

void Tile::setSquare(Square square) {
    m_square = square;
    if ((square.file - 'A' + square.rank) % 2) {
        m_rank_label.setColor(sf::Color(255, 255, 221));
        m_file_label.setColor(sf::Color(255, 255, 221));
        setColor(sf::Color(134, 166, 102));
    } else {
        m_rank_label.setColor(sf::Color(134, 166, 102));
        m_file_label.setColor(sf::Color(134, 166, 102));
        setColor(sf::Color(255, 255, 221));
    }

    setLabel();
}

Square Tile::getSquare() { return m_square; }

void Tile::setFlipped(bool flipped) {
    m_flipped = flipped;
    setLabel();
}

void Tile::setLabel() {
    if (!m_flipped) {
        if (m_square.file == 'H')
            m_file_label.setText(std::to_string(m_square.rank));
        else
            m_file_label.setText("");
        if (m_square.rank == 1)
            m_rank_label.setText(std::string(1, m_square.file));
        else
            m_rank_label.setText("");
    } else {
        if (m_square.file == 'A')
            m_file_label.setText(std::to_string(m_square.rank));
        else
            m_file_label.setText("");
        if (m_square.rank == 8)
            m_rank_label.setText(std::string(1, std::tolower(m_square.file)));
        else
            m_rank_label.setText("");
    }
}

}  // namespace Chess
