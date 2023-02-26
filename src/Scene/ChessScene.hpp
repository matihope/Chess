#pragma once
#include <Chess/Chess.hpp>
#include <GUI/GUI.hpp>
#include <Scene/Scene.hpp>
#include <vector>

class ChessScene : public Scene {
   private:
    std::vector<Chess::Tile*> m_board;
    Chess::Manager m_chess_manager;

   public:
    bool load();
    void update(const float& dt) override;
};
