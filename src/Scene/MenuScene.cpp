#include <Scene/MenuScene.hpp>
#include <Scene/ChessScene.hpp>
#include <TileMap/TileMap.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

bool MenuScene::load() {
    auto btn = std::make_unique<GUI::Button>(m_game->getFont(), "Play");
    m_play_btn = btn.get();
    m_play_btn->setPosition(int(m_game->getViewportSize().x / 2), int(m_game->getViewportSize().y / 2));
    m_play_btn->setTextSize(64);
    addEntity(std::move(btn));

    return true;
}

void MenuScene::update(const float& dt) {
    Scene::update(dt);

    if(m_play_btn->isPressed()) {
        auto gameScene = std::make_unique<ChessScene>();
        m_game->replaceTopScene(std::move(gameScene));
    }

}
