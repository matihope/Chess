#include <Game/Game.hpp>
#include "Scenes/MenuScene.hpp"
#include <memory>

int main() {
  Game &game = Game::get();
  if (!game.init("settings.json")) return 1;

  game.addScene(std::make_unique<MenuScene>());

  while (game.isRunning()) {
    game.pollEvents();
    game.update();
    game.draw();
  }
}
