#include <Scene/MenuScene.hpp>
#include <Scene/ChessScene.hpp>
#include <TileMap/TileMap.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

MenuScene::MenuScene() : WorldEntity() {
    auto btn = std::make_unique<GUI::Button>(Game::get().getFont(), "Play");
    m_play_btn = btn.get();
    m_play_btn->setPosition(int(Game::get().getViewportSize().x / 2),
                            int(Game::get().getViewportSize().y / 2));
    m_play_btn->setTextSize(64);
    m_play_btn->setClickMode(Clickable::ClickMode::PressOnRelease);
    addChild(std::move(btn));
}

void MenuScene::update(const float dt) {
    WorldEntity::update(dt);

    if(m_play_btn->isPressed()) {
        auto gameScene = std::make_unique<ChessScene>();
        Game::get().replaceTopScene(std::move(gameScene));
    }
}
