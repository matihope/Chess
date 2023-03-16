#include <Scenes/MenuScene.hpp>
#include <Scenes/ChessScene.hpp>
#include <TileMap/TileMap.hpp>
#include <CollisionComponent/CollisionComponent.hpp>
#include <GUI/GUI.hpp>
#include <Game/Game.hpp>

MenuScene::MenuScene() : WorldEntity() {
  m_play_btn = addChild<GUI::Button>(Game::get().getFont(), "Play");
  m_play_btn->setPosition(int(Game::get().getViewportSize().x / 2),
                          int(Game::get().getViewportSize().y / 2));
  m_play_btn->setTextSize(64);
  m_play_btn->setClickMode(Clickable::ClickMode::PressOnRelease);
}

void MenuScene::update(const float dt) {
  WorldEntity::update(dt);

  if (m_play_btn->isPressed()) {
    auto gameScene = std::make_unique<ChessScene>();
    Game::get().replaceTopScene(std::move(gameScene));
  }
}
