#include <Game/Game.hpp>
#include <SFML/Graphics.hpp>
#include <Scene/MenuScene.hpp>
#include <memory>

int main(){
    Game& game = Game::get();
    if (!game.init("settings.json")) return 1;

    auto menuScene = std::make_unique<MenuScene>();
    game.addScene(std::move(menuScene));

    while (game.isRunning()) {
        game.pollEvents();
        game.update();
        game.draw();
    }
}
