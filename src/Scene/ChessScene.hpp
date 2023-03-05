#pragma once
#include <Chess/Chess.hpp>
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>
#include <vector>

class ChessScene : public WorldEntity {
   private:
    Chess::BoardManager* m_board;

   public:
    ChessScene();
};
