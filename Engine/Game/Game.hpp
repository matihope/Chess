#pragma once
#include <SFML/Graphics.hpp>
#include <Updatable/Updatable.hpp>
#include <JsonBridge/JsonBridge.hpp>
#include <GUI/Label.hpp>
#include <memory>
#include <iostream>
#include <stack>

class Scene;

class Game {

    // varibles
    bool m_run = true;
    float m_dt = 0; // delta time
    double m_fps_sum = 0.0;
    unsigned int m_fps_frame_count = 0;
    bool m_enable_print_fps = false;
    float m_physics_update_call_freq;
    float m_physics_update_counter = 0.f;

    // objects
    sf::Clock m_clock;
    JsonBridge m_game_settings;
    sf::RenderWindow m_window;
    std::stack<std::unique_ptr<Scene>> m_scenes_stack;
    sf::View m_view;
    sf::Font m_font;
    GUI::Label m_fps_label;

    // internal methods
    Game(){};
    static Game& get();
    bool Iinit(std::string settingsPath);
    void Idraw();
    void Iupdate();


    public:
        ~Game();
        static bool init(std::string settingsPath);
        static void draw();
        static void update();
        static void pollEvents();
        static void setPrintFPS(const bool& printFPS);
        static void stop();
        static bool isRunning();
        static const sf::Vector2u getWindowSize();
        static const sf::Vector2u getViewportSize();
        static const sf::RenderWindow& getRenderWindow();
        static void updateViewportSize();
        static bool addScene(std::unique_ptr<Scene> newScene);
        static bool replaceTopScene(std::unique_ptr<Scene> newScene);
        static void popScene();
        static sf::Vector2f getMousePos();
        static sf::Font* getFont();
        static sf::View* getView();
        static bool isRectInsideView(const sf::FloatRect& rect);
        static void setCameraCenter(const sf::Vector2f& pos);
};
