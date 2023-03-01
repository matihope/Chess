#pragma once
#include <Chess/Chess.hpp>
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>

class ChessScene : public WorldEntity {
   private:
    std::vector<Chess::Tile*> m_board;
    Chess::GameOfChess m_chess_manager;

   public:
    ChessScene();
    void update(const float dt) override;
    void tilePressed(Chess::Tile* tile);
};
