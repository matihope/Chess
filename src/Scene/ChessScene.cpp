
#include <Chess/Tile.hpp>
#include <ResourceManager/ResourceManager.hpp>
#include <Scene/ChessScene.hpp>
#include <iostream>

ChessScene::ChessScene() : WorldEntity() {
    ResourceManager::get().setTextureSmooth("../resources/chess_pieces.png", true);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; ++y) {
            auto ct = std::make_unique<Chess::Tile>();
            ct->setSize(100.f);
            Chess::Tile* chess_tile = ct.get();
            chess_tile->setSize(100.f);
            chess_tile->setPosition(100.f * (7 - x), 100.f * (7 - y));
            chess_tile->setFlipped(true);
            m_board.push_back(chess_tile);
            addChild(std::move(ct));

            auto sq = Chess::Square('A' + x, 8 - y);
            chess_tile->setSquare(sq);
            chess_tile->setPiece(m_chess_manager.getPieceAt(sq));
        }
    }
}

void ChessScene::tilePressed(Chess::Tile* tile) {
    Chess::Square sq = tile->getSquare();
    std::cout << "Pressed! My pos is: " << sq.file << " " << sq.rank << std::endl;
}

void ChessScene::update(const float dt) { WorldEntity::update(dt); }
