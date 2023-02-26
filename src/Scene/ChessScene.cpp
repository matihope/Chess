#include <Chess/Tile.hpp>
#include <Scene/ChessScene.hpp>
#include <ResourceManager/ResourceManager.hpp>

bool ChessScene::load() {
    ResourceManager::setTextureSmooth("../resources/chess_pieces.png", true);

    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; ++y) {
            auto ct = std::make_unique<Chess::Tile>();
            ct->setSize(100.f);
            Chess::Tile* chess_tile = ct.get();
            chess_tile->setSize(100.f);
            chess_tile->setPosition(100.f * x, 100.f * y);
            m_board.push_back(chess_tile);
            addEntity(std::move(ct));

            if ((x + y) % 2)
                chess_tile->setColor(sf::Color(134, 166, 102));
            else
                chess_tile->setColor(sf::Color(255, 255, 221));
            chess_tile->setPiece(m_chess_manager.getPieceAt('A' + x, 8 - y));
        }
    }
    return true;
}

void ChessScene::update(const float& dt) { Scene::update(dt); }
