
#include <ResourceManager/ResourceManager.hpp>
#include "Scenes/ChessScene.hpp"
#include <Chess/BoardEntity.hpp>
#include <memory>
#include "Chess/Tile.hpp"
#include "Game/Game.hpp"
#include <SFML/Audio.hpp>

ChessScene::ChessScene() : WorldEntity() {
  // create board representation
  m_board_entity = addChild<BoardEntity>(BOARD_SIZE, TILE_SIZE);
  m_piece_is_floating = false;

  // create floating piece
  m_floating_piece = addChild<FloatingPiece>(TILE_SIZE);
  m_floating_piece->hide();
  m_is_piece_selected = false;

  // load clicky tiles
  for (int x = 0; x < 8; ++x) {
    for (int y = 0; y < 8; ++y) {
      Chess::Position pos((char) ('A' + x), y + 1);
      auto &tile = m_tiles[(y * BOARD_SIZE) + x];
      tile = addChild<Tile>(pos);
      tile->setSize(TILE_SIZE);
      tile->setPosition(sf::Vector2f(TILE_SIZE * (float) x, TILE_SIZE * (float) (7 - y)));
    }
  }
  reloadBoardPieces();
  playSound("start");
}

void ChessScene::onUpdate(float dt) {
  sf::Cursor::Type new_cursor_type = sf::Cursor::Arrow;
  sf::Vector2f mouse_pos = Game::get().getMousePos();
  for (auto *tile : m_tiles) {
    if (tile->contains(mouse_pos) and not m_chess_game.isSquareEmpty(tile->getPosition()))
      new_cursor_type = sf::Cursor::Hand;

    // on tile click
    if (tile->isPressed()) {
      Chess::Position position = tile->getPosition();
      bool made_a_move = false;
      if (m_is_piece_selected and m_chess_game.isMovePossible(m_held_piece_position, position)) {
        made_a_move = true;
        makeMove(m_held_piece_position, position);
      }
      if (not made_a_move and not m_chess_game.isSquareEmpty(position)) {
        // mark available moves
        applyBoardMarks(m_chess_game.getAvailableMovesAt(position));
        // start dragging a piece
        reloadBoardPieces();
        m_board_entity->clearSquare(position);
        m_floating_piece->setPieceInfo(m_chess_game.getPieceAt(position)->getInfo());
        m_piece_is_floating = true;
        if (not m_chess_game.isSquareEmpty(m_held_piece_position))
          m_board_entity->pressSquare(m_held_piece_position, false);

        m_board_entity->pressSquare(position, true);
        m_held_piece_position = position;
        m_is_piece_selected = true;
      } else {
        m_is_piece_selected = false;
        reloadBoardEffects();
      }
    }
  }

  // on piece drop
  if (m_piece_is_floating and not sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    reloadBoardPieces();
    m_board_entity->clearHighlight();
    m_piece_is_floating = false;
    m_floating_piece->hide();
    // find correct tile
    for (auto tile : m_tiles) {
      if (tile->contains(mouse_pos)) {
        makeMove(m_held_piece_position, tile->getPosition());
        break;
      }
    }
  }

  // update floating piece's position
  if (m_piece_is_floating) {
    new_cursor_type = sf::Cursor::Hand;
    m_floating_piece->show();
    m_floating_piece->setPosition(Game::get().getMousePos());
    // find tile to highlight
    m_board_entity->clearHighlight();
    for (auto tile : m_tiles) {
      if (tile->contains(mouse_pos)) {
        m_board_entity->highlightSquare(tile->getPosition());
      }
    }
  }
  Game::get().setCursor(new_cursor_type);
}

void ChessScene::reloadBoardPieces() {
  for (unsigned int x = 0; x < 8; x++) {
    for (unsigned int y = 0; y < 8; y++) {
      Chess::Position pos((char) ('A' + x), y + 1);
      auto piece = m_chess_game.getPieceAt(pos);
      if (piece == nullptr) {
        m_board_entity->clearSquare(pos);
      } else {
        m_board_entity->setPieceOnSquare(pos, piece->getType(), piece->getColor());
      }
    }
  }
}

void ChessScene::handleEvent(const sf::Event &event) {
  switch (event.type) {
    case sf::Event::KeyPressed: {
      if (event.key.code == sf::Keyboard::Left) undoLastMove();
      if (event.key.code == sf::Keyboard::Right) redoLastMove();
    }
      break;
    default:break;
  }
}

bool ChessScene::undoLastMove() {
  playMoveSound();
  bool undid = m_chess_game.undoLastMove();
  if (undid)
    reloadBoardEffects();
  return undid;
}

bool ChessScene::redoLastMove() {
  bool redid = m_chess_game.redoLastMove();
  if (redid) {
    reloadBoardEffects();
    playMoveSound();
  }
  return redid;
}

bool ChessScene::makeMove(Chess::Position start, Chess::Position end) {
  if (start == end)
    return false;
  m_is_piece_selected = false;

  bool made_a_move = m_chess_game.makeMove(start, end);
  if (made_a_move) {
    reloadBoardEffects();
    playMoveSound();
  } else {
    bool white_checked = m_chess_game.isKingChecked(Chess::Color::White);
    bool black_checked = m_chess_game.isKingChecked(Chess::Color::Black);
    if (white_checked or black_checked) {
      playSound("king_alert");
    }
  }
  return made_a_move;
}

void ChessScene::reloadBoardEffects() {
  m_board_entity->clearPress();
  m_board_entity->clearMark();
  auto last_move = m_chess_game.getLastMove();
  if (last_move != nullptr) {
    m_board_entity->pressSquare(last_move->getStart(), true);
    m_board_entity->pressSquare(last_move->getEnd(), true);
  }
  reloadBoardPieces();

}

void ChessScene::playMoveSound() {
  if (m_chess_game.getLastMove() == nullptr)
    return;

  bool has_captured_a_piece = m_chess_game.getLastMove()->hasCapturedPiece();
  bool white_checked = m_chess_game.isKingChecked(Chess::Color::White);
  bool black_checked = m_chess_game.isKingChecked(Chess::Color::Black);

  std::string to_play = "move";
  if (has_captured_a_piece)
    to_play = "capture";
  if (white_checked or black_checked)
    to_play = "check";

  playSound(to_play);
}

void ChessScene::playSound(const std::string &name) {
  m_sound.setBuffer(ResourceManager::get().getSoundBuffer("../resources/sounds/" + name + ".wav"));
  m_sound.play();
}

void ChessScene::applyBoardMarks(const std::vector<Chess::Position> &moves) {
  m_board_entity->clearMark();
  for (auto move : moves) {
    m_board_entity->markSquare(move, 1);
    if (not m_chess_game.isSquareEmpty(move))
      m_board_entity->markSquare(move, 2);
  }
}
