#include <SFML/Graphics.hpp>
#include <Game/Game.hpp>
#include <memory>
#include <Scene/MenuScene.hpp>

int main(){

    if(!Game::init("settings.json"))
        return 1;

    auto menuScene = std::make_unique<MenuScene>();
    Game::addScene(std::move(menuScene));

    while(Game::isRunning()){
        Game::pollEvents();
        Game::update();
        Game::draw();
    }
}
