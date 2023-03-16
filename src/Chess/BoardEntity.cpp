//
// Created by mateusz on 3/10/23.
//

#include "BoardEntity.hpp"
#include "Game/Game.hpp"
#include <ResourceManager/ResourceManager.hpp>

BoardEntity::BoardEntity(const int board_size, const float tile_size) : BOARD_SIZE(board_size), TILE_SIZE(tile_size) {

  // load textures
  ResourceManager::get().setTextureSmooth("../resources/chess_pieces.png", true);
  ResourceManager::get().setTextureSmooth("../resources/chess_colors.png", false);
  ResourceManager::get().setTextureSmooth("../resources/chess_marks.png", true);
  const sf::Texture *board_texture = &ResourceManager::get().getTexture("../resources/chess_colors.png");
  const sf::Texture *pieces_texture = &ResourceManager::get().getTexture("../resources/chess_pieces.png");
  const sf::Texture *marks_texture = &ResourceManager::get().getTexture("../resources/chess_marks.png");

  // set batches
  // board
  m_board_batch = addChild<SpriteBatch>(board_texture);
  m_board_batch->makeGrid({BOARD_SIZE, BOARD_SIZE}, {TILE_SIZE, TILE_SIZE});
  // pressed
  m_pressed_batch = addChild<SpriteBatch>(board_texture);
  m_pressed_batch->makeGrid({BOARD_SIZE, BOARD_SIZE}, {TILE_SIZE, TILE_SIZE});
  // highlight
  m_highlight_batch = addChild<SpriteBatch>(board_texture);
  m_highlight_batch->makeGrid({BOARD_SIZE, BOARD_SIZE}, {TILE_SIZE, TILE_SIZE});
  // mark
  m_mark_batch = addChild<SpriteBatch>(marks_texture);
  m_mark_batch->makeGrid({BOARD_SIZE, BOARD_SIZE}, {TILE_SIZE, TILE_SIZE});
  //pieces
  m_pieces_batch = addChild<SpriteBatch>(pieces_texture);
  m_pieces_batch->makeGrid({BOARD_SIZE, BOARD_SIZE}, {TILE_SIZE, TILE_SIZE});

  // prepare the labels
  for (auto &label : m_labels) {
    label = addChild<GUI::Label>(Game::get().getFont());
    label->setPosition(50, 50);
    label->setText("HELLO");
    label->setTextSize(16);
  }

  // get colors for labels
  auto label_light_color = board_texture->copyToImage().getPixel(16, 0);
  auto label_dark_color = board_texture->copyToImage().getPixel(32, 0);

  // setup board's colors and labels
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {

      // set square's appropriate color
      QuickSprite board_sprite = m_board_batch->getSprite(y * BOARD_SIZE + x);
      board_sprite.setTexSize(sf::Vector2f(16.f, 16.f));
      if ((x + y) % 2 == 0)
        board_sprite.setTexPosition(sf::Vector2f(16.0, 0));
      else
        board_sprite.setTexPosition(sf::Vector2f(32.0, 0));

      // and lastly, the labels
      if (x == BOARD_SIZE - 1) {
        // rank label
        GUI::Label &label = *m_labels[8 + y];
        label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);
        label.setPosition((x + 1) * TILE_SIZE, y * TILE_SIZE);
        label.move(-TILE_SIZE / 20.f, TILE_SIZE / 20.f);
        label.setText(std::to_string(8 - y));
        if (y % 2)
          label.setColor(label_dark_color);
        else
          label.setColor(label_light_color);
      }
      if (y == BOARD_SIZE - 1) {
        // file label
        GUI::Label &label = *m_labels[x];
        label.setAlignment(GUI::HAlignment::LEFT, GUI::VAlignment::BOTTOM);
        label.setPosition(x * TILE_SIZE, (y + 1) * TILE_SIZE);
        label.move(TILE_SIZE / 20.f, -TILE_SIZE / 20.f);
        label.setText(std::string(1, (char) (x + 'a')));
        if (x % 2)
          label.setColor(label_dark_color);
        else
          label.setColor(label_light_color);
      }
    }
  }
}

void BoardEntity::clearSquare(Chess::Position position) {
  getPiecesSpriteAt(position).clear();
}

void BoardEntity::setPieceOnSquare(Chess::Position position, Chess::PieceType type, Chess::Color color) {
  QuickSprite sprite = getPiecesSpriteAt(position);
  auto [tex_x, tex_y] = m_pieces_batch->getTexture()->getSize();
  float x = (float) type * tex_x / 6.f;
  float y = (float) color * tex_y / 2.f;
  sprite.setTexPosition(sf::Vector2f(x, y));
  sprite.setTexSize(sf::Vector2f(tex_x / 6.f, tex_y / 2.f));
}

QuickSprite BoardEntity::getPiecesSpriteAt(Chess::Position position) {
  return m_pieces_batch->getSprite(getArrayIndex(position));
}

void BoardEntity::setSquaresDefaultColors() {
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      Chess::Position position(x + 'A', y + 1);
      pressSquare(position, true);
    }
  }
}

void BoardEntity::pressSquare(Chess::Position position, bool press) {
  QuickSprite sprite = m_pressed_batch->getSprite(getArrayIndex(position));
  if (press) {
    sprite.setTexPosition({48.f, 0.f});
    sprite.setTexSize({16.f, 16.f});
  } else {
    sprite.clear();
  }
}

void BoardEntity::highlightSquare(Chess::Position position) {
  QuickSprite sprite = m_highlight_batch->getSprite(getArrayIndex(position));
  sprite.setTexPosition({64.f, 0.f});
  sprite.setTexSize({16.f, 16.f});
}

std::pair<unsigned int, unsigned int> BoardEntity::getArrayCoords(Chess::Position position) {
  unsigned int x = position.file - 'A';
  unsigned int y = 8 - position.rank;
//  if (m_flipped) {
//    x = 8 - position.file + 'A';
//    y = position.rank - 1;
//  }
  return {x, y};
}

unsigned int BoardEntity::getArrayIndex(Chess::Position position) {
  auto [x, y] = getArrayCoords(position);
  return y * BOARD_SIZE + x;
}

void BoardEntity::clearHighlight() {
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      m_highlight_batch->getSprite(y * BOARD_SIZE + x).clear();
    }
  }
}

void BoardEntity::clearPress() {
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      m_pressed_batch->getSprite(y * BOARD_SIZE + x).clear();
    }
  }
}

void BoardEntity::markSquare(Chess::Position position, unsigned int level) {
  QuickSprite sprite = m_mark_batch->getSprite(getArrayIndex(position));
  if (level == 0) {
    sprite.clear();
  } else {
    sprite.setTexPosition({(level - 1) * 256.f, 0.f});
    sprite.setTexSize({256.f, 256.f});
  }
}

void BoardEntity::clearMark() {
  for (int x = 0; x < BOARD_SIZE; x++) {
    for (int y = 0; y < BOARD_SIZE; y++) {
      m_mark_batch->getSprite(y * BOARD_SIZE + x).clear();
    }
  }
}
