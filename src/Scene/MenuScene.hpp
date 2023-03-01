#pragma once
#include <GUI/GUI.hpp>
#include <WorldEntity/WorldEntity.hpp>

class MenuScene : public WorldEntity {
    GUI::Button* m_play_btn;
    std::unique_ptr<sf::Texture> background;

    public:
     MenuScene();
     void update(const float dt) override;
};
