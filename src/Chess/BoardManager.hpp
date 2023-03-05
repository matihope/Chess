#pragma once
#include <Chess/GameOfChess.hpp>
#include <Chess/Tile.hpp>
#include <WorldEntity/WorldEntity.hpp>

namespace Chess {
class BoardManager : public WorldEntity {
    std::list<Tile*> m_board;
    GameOfChess m_chess_manager;

   public:
    BoardManager();
    void tilePressed(Tile* tile);
    
};
}  // namespace Chess
