//
// Created by mateusz on 3/10/23.
//

#include "BoardEntity.hpp"
#include "Game/Game.hpp"
#include <ResourceManager/ResourceManager.hpp>

BoardEntity::BoardEntity(const int board_size, const float tile_size) : BOARD_SIZE(board_size), TILE_SIZE(tile_size) {

  // load textures
  ResourceManager::get().setTextureSmooth("../resources/chess_pieces.png", true);
  m_board_texture = &ResourceManager::get().getTexture("../resources/chess_colors.png");
  m_pieces_texture = &ResourceManager::get().getTexture("../resources/chess_pieces.png");

  // prepare the labels
  for(auto & label : m_labels) {
    auto label_ptr = std::make_unique<GUI::Label>();
    label = label_ptr.get();
    label->setFont(Game::get().getFont());
    addChild(std::move(label_ptr));
    label->setPosition(50, 50);
    label->setText("HELLO");
    label->setTextSize(16);
  }
  // label dark color:
  auto label_light_color = m_board_texture->copyToImage().getPixel(0, 1);
  auto label_dark_color = m_board_texture->copyToImage().getPixel(17, 1);

  // setup vertices
  m_board_vertices.resize(BOARD_SIZE * BOARD_SIZE * 4);
  m_board_vertices.setPrimitiveType(sf::Quads);
  m_pieces_vertices.resize(BOARD_SIZE * BOARD_SIZE * 4);
  m_pieces_vertices.setPrimitiveType(sf::Quads);
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {

      // first, the board
      sf::Vertex *quad = &m_board_vertices[((y * BOARD_SIZE) + x) * 4];
      quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
      quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
      quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
      quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

      // square's appropriate color
      if ((x + y) % 2 == 0) {
        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(16.f, 0);
        quad[2].texCoords = sf::Vector2f(16.f, 16.f);
        quad[3].texCoords = sf::Vector2f(0, 16.f);
      } else {
        quad[0].texCoords = sf::Vector2f(16.f, 0);
        quad[1].texCoords = sf::Vector2f(32.f, 0);
        quad[2].texCoords = sf::Vector2f(32.f, 16.f);
        quad[3].texCoords = sf::Vector2f(16.f, 16.f);
      }

      // now prepare vertex array for pieces
      quad = &m_pieces_vertices[((y * BOARD_SIZE) + x) * 4];
      quad[0].position = sf::Vector2f(x * TILE_SIZE, y * TILE_SIZE);
      quad[1].position = sf::Vector2f((x + 1) * TILE_SIZE, y * TILE_SIZE);
      quad[2].position = sf::Vector2f((x + 1) * TILE_SIZE, (y + 1) * TILE_SIZE);
      quad[3].position = sf::Vector2f(x * TILE_SIZE, (y + 1) * TILE_SIZE);

      // and lastly, the labels
      if(x == BOARD_SIZE - 1) {
        // rank label
        GUI::Label &label = *m_labels[8 + y];
        label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);
        label.setPosition((x + 1) * TILE_SIZE, y * TILE_SIZE);
        label.move(-TILE_SIZE/20.f, TILE_SIZE/20.f);
        label.setText(std::to_string(y + 1));
        if(y % 2)
          label.setColor(label_dark_color);
        else
          label.setColor(label_light_color);
      }
      if (y == BOARD_SIZE - 1) {
        // file label
        GUI::Label &label = *m_labels[x];
        label.setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::BOTTOM);
        label.setPosition(x * TILE_SIZE, (y + 1) * TILE_SIZE);
        label.move(TILE_SIZE/20.f, -TILE_SIZE/20.f);
        label.setText(std::string(1, (char)(x + 'a')));
        if(x % 2)
          label.setColor(label_dark_color);
        else
          label.setColor(label_light_color);
      }
    }
  }
}

void BoardEntity::onDraw(sf::RenderTarget &target, sf::RenderStates states) const {
  states.transform *= getTransform();

  sf::RenderStates board_states(states);
  sf::RenderStates pieces_states(states);

  board_states.texture = m_board_texture;
  target.draw(m_board_vertices, board_states);
  pieces_states.texture = m_pieces_texture;
  target.draw(m_pieces_vertices, pieces_states);
}

void BoardEntity::clearSquare(Chess::Position position) {
  sf::Vertex *quad = getPiecesQuadAt(position);
  quad[0].texCoords = quad[1].texCoords = quad[2].texCoords = quad[3].texCoords = sf::Vector2f(0.f, 0.f);
}

void BoardEntity::setPieceOnSquare(Chess::Position position, Chess::PieceType type, Chess::Color color) {
  sf::Vertex *quad = getPiecesQuadAt(position);
  setQuadPieceTexCoords(quad, type, color);

}

void BoardEntity::setQuadPieceTexCoords(sf::Vertex *quad, Chess::PieceType type, Chess::Color color) {
  auto [tex_x, tex_y] = m_pieces_texture->getSize();
  float x = (float) type * tex_x / 6.f;
  float y = (float) color * tex_y / 2.f;
  quad[0].texCoords = sf::Vector2f(x, y);
  quad[1].texCoords = sf::Vector2f(x + tex_x / 6.f, y);
  quad[2].texCoords = sf::Vector2f(x + tex_x / 6.f, y + tex_y / 2.f);
  quad[3].texCoords = sf::Vector2f(x, y + tex_y / 2.f);
}

sf::Vertex *BoardEntity::getPiecesQuadAt(Chess::Position position) {
  unsigned int x = position.file - 'A';
  unsigned int y =  8 - position.rank;
  return &m_pieces_vertices[((y * BOARD_SIZE) + x) * 4];
}
