#pragma once
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>
#include <Chess/Logic/Board.hpp>
#include "Chess/Logic/Pieces/BasePiece.hpp"
#include <Chess/BoardEntity.hpp>
#include <Chess/Logic/Game.hpp>
#include "Chess/Tile.hpp"
#include "Chess/FloatingPiece.hpp"
#include <SFML/Audio.hpp>

class ChessScene : public WorldEntity {
 public:
  ChessScene();
 private:
  const int BOARD_SIZE = 8; // DON'T CHANGE
  const float TILE_SIZE = 100.;
  bool m_piece_is_floating;
  Chess::Game m_chess_game;
  BoardEntity *m_board_entity;
  std::array<Tile *, 64> m_tiles;
  FloatingPiece *m_floating_piece;
  Chess::Position m_held_piece_position;
  bool m_is_piece_selected;
  sf::Sound m_sound;

  void reloadBoardPieces();
  void onUpdate(float dt) override;
  void handleEvent(const sf::Event &event) override;
  bool makeMove(Chess::Position start, Chess::Position end);
  bool undoLastMove();
  bool redoLastMove();
  void reloadBoardEffects();
  void applyBoardMarks(const std::vector<Chess::Position> &moves);
  void playSound(const std::string &name);
  void playMoveSound();
};
