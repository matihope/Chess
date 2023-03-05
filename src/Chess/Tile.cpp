#include "Tile.hpp"

#include <Chess/BoardManager.hpp>
#include <Chess/Tile.hpp>
#include <Game/Game.hpp>
#include <iostream>

namespace Chess {
Tile::Tile() : m_collision_shape(RectCollision(this)) {
    m_shape = sf::RectangleShape();
    m_piece.setType(Chess::PieceType::Empty);

    m_flipped = false;
    m_rank_label.setFont(Game::get().getFont());
    m_file_label.setFont(Game::get().getFont());
    m_rank_label.setTextSize(16);
    m_file_label.setTextSize(16);
    m_rank_label.setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::BOTTOM);
    m_file_label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);

    m_show_move_indicator = false;
    m_move_indicator.setFillColor(sf::Color(21, 21, 21, 30));
    m_move_indicator.setPosition(50.f, 50.f);
    m_dot_percentage = 17;
}

Tile::Tile(Square square) : Tile::Tile() { setSquare(square); }

void Tile::setColor(sf::Color color) { m_shape.setFillColor(color); }

void Tile::setSize(float size) {
    m_collision_shape.setSize(size, size);
    setClickCollisionShape(&m_collision_shape);
    m_shape.setSize(sf::Vector2f(size, size));
    uint buffer = 3;

    m_rank_label.setPosition(sf::Vector2f(buffer, size - buffer));
    m_file_label.setPosition(sf::Vector2f(size - buffer, buffer));
}

float Tile::getSize() { return m_shape.getSize().x; }

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
    if (m_show_move_indicator) {
        target.draw(m_move_indicator, states);
    }
    WorldEntity::draw(target, states);
}

void Tile::update(const float dt) {
    Clickable::update(dt);
    WorldEntity::update(dt);
}

void Tile::selfReleased() {
    BoardManager* parent = dynamic_cast<BoardManager*>(getParent());
    parent->tilePressed(this);
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

void Tile::setMoveIndicator(bool show) {
    m_show_move_indicator = show;
    if (show) {
        if (m_piece.getType() == PieceType::Empty) {
            // m_move_indicator.setPosition();
            // m_move_indicator.setRadius(.f);
        } else {
            m_move_indicator.setRadius(getSize() * m_dot_percentage / 100.0f);
            float pos = getSize() / 2 - getSize() * m_dot_percentage / 100.0f;
            m_move_indicator.setPosition(pos, pos);
        }
    }
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
