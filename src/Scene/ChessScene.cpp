
#include <ResourceManager/ResourceManager.hpp>
#include <Scene/ChessScene.hpp>
#include <iostream>
#include "ChessScene.hpp"

ChessScene::ChessScene() : WorldEntity() {
    ResourceManager::get().setTextureSmooth("../resources/chess_pieces.png", true);
    auto board = std::make_unique<Chess::BoardManager>();
    m_board = board.get();
    addChild(std::move(board));
}
