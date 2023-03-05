#include "BoardManager.hpp"

#include <Chess/BoardManager.hpp>
#include <Chess/Square.hpp>
#include <Chess/Tile.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <iostream>

namespace Chess {
BoardManager::BoardManager() {
    // ResourceManager::get().setTextureSmooth("../resources/chess_pieces.png", true);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; ++y) {
            auto ct = std::make_unique<Chess::Tile>();
            ct->setSize(100.f);
            Chess::Tile* chess_tile = ct.get();
            chess_tile->setSize(100.f);
            chess_tile->setPosition(100.f * x, 100.f * y);
            m_board.push_back(chess_tile);
            addChild(std::move(ct));

            auto sq = Chess::Square('A' + x, (8 - y));
            chess_tile->setSquare(sq);
            chess_tile->setPiece(m_chess_manager.getPieceAt(sq));
        }
    }
}
void BoardManager::tilePressed(Tile* tile) {
    std::vector<Square> avaliable_moves = m_chess_manager.getAvailableMovesAt(tile->getSquare());
    for (auto& available_move : avaliable_moves) {
        for(auto& m_tile : m_board) {
            if(m_tile->getSquare() == available_move) {
                m_tile->setMoveIndicator(true);
            }
        }
    }
}
}  // namespace Chess
