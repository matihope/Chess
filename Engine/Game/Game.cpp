
#include <CollisionComponent/CollisionComponent.hpp>
#include <Game/Game.hpp>
#include <SFML/Graphics.hpp>
#include <Scene/Scene.hpp>
#include <iostream>
#include <iterator>

sf::Vector2f scaleToFit(const sf::Vector2f viewSize, const sf::Vector2u windowSize) {
    sf::Vector2f scale;
    scale.x = viewSize.x / windowSize.x;
    scale.y = viewSize.y / windowSize.y;
    if (scale.x < scale.y) {
        scale.x *= 1 / scale.y;
        scale.y = 1;
    } else {
        scale.y *= 1 / scale.x;
        scale.x = 1;
    }
    return scale;
}

Game& Game::get() {
    static Game instance;
    return instance;
}
bool Game::Iinit(std::string settingsPath) {  // initialize variables
    if (!m_game_settings.load("settings.json")) {
        std::cout
            << "Could not load settings.json. Make sure settings.json is inside the src folder."
            << std::endl;
        return false;
    }

    m_window.create(sf::VideoMode(m_game_settings.data["window"]["width"],
                                  m_game_settings.data["window"]["height"]),
                    std::string(m_game_settings.data["window"]["title"]), sf::Style::Default,
                    sf::ContextSettings(0, 0, 4));
    m_window.setVerticalSyncEnabled(m_game_settings.data["window"]["vsync"]);

    m_view.reset(sf::FloatRect(0.f, 0.f, m_game_settings.data["viewport"]["width"],
                               m_game_settings.data["viewport"]["height"]));
    updateViewportSize();

    setPrintFPS(m_game_settings.data["debug"]["printFPS"]);
    m_physics_update_call_freq = 1.f / int(m_game_settings.data["engine"]["physicsUpdateCallFreq"]);
    if (!m_font.loadFromFile(m_game_settings.data["engine"]["fontPath"])) {
        std::cout << "Failed to load font" << std::endl;
    }
    Debug::setDebugCollisionDraw(m_game_settings.data["debug"]["drawCollisionShapes"]);

    m_fps_label.setPosition(float(m_game_settings.data["viewport"]["width"]) - 1, 1);
    m_fps_label.setFont(getFont());
    m_fps_label.setText("0");
    m_fps_label.setTextSize(32);
    m_fps_label.setAlignment(GUI::HAlignment::RIGHT, GUI::VAlignment::TOP);

    return true;
}
bool Game::init(const std::string settingsPath) { return get().Iinit(settingsPath); }
Game::~Game() { get().m_window.close(); }

void Game::Idraw() {
    m_window.clear(sf::Color(21, 21, 21));

    if (!m_scenes_stack.empty()) m_scenes_stack.top()->draw(m_window);

    if (m_enable_print_fps) m_window.draw(m_fps_label);

    m_window.display();
}
void Game::draw() { get().Idraw(); }

void Game::Iupdate() {
    m_dt = m_clock.restart().asSeconds();

    if (!m_scenes_stack.empty()) {
        m_scenes_stack.top()->cleanEntities();
        m_physics_update_counter += m_dt;
        if (m_physics_update_counter >= m_physics_update_call_freq) {
            m_scenes_stack.top()->physicsUpdate(m_physics_update_call_freq);
            m_physics_update_counter -= m_physics_update_call_freq;
        }
        m_scenes_stack.top()->update(m_dt);
    }

    // recalculate avg fps
    if (m_enable_print_fps) {
        m_fps_frame_count++;
        m_fps_sum += m_dt;
        if (m_fps_sum >= 1.f) {
            int currentFps = round(m_fps_frame_count / m_fps_sum);
            m_fps_label.setText(std::to_string(currentFps));
            m_fps_sum = 0.0;
            m_fps_frame_count = 0;
        }
    }
}

void Game::update() { get().Iupdate(); }

bool Game::addScene(std::unique_ptr<Scene> newScene) {
    newScene->addGame(&get());
    bool returnValue = newScene->load();
    get().m_scenes_stack.push(std::move(newScene));
    return returnValue;
}

void Game::popScene() {
    get().m_scenes_stack.top()->kill();
    get().m_scenes_stack.pop();
}

bool Game::replaceTopScene(std::unique_ptr<Scene> newScene) {
    get().m_scenes_stack.pop();
    return addScene(std::move(newScene));
}

void Game::pollEvents() {
    sf::Event event;
    while (get().m_window.pollEvent(event)) {
        if (!get().m_scenes_stack.empty()) get().m_scenes_stack.top()->handleEvent(event);

        switch (event.type) {
            case sf::Event::Closed:
                stop();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Escape:
                        stop();
                        break;
                    default:
                        // skip any other case
                        break;
                }
                break;
            case sf::Event::Resized:
                updateViewportSize();
                break;
            default:
                // skip any other case
                break;
        }
    }
}

bool Game::isRunning() { return get().m_run; }

void Game::stop() { get().m_run = false; }

void Game::setPrintFPS(const bool& printFPS) { get().m_enable_print_fps = printFPS; }

const sf::Vector2u Game::getWindowSize() { return get().m_window.getSize(); }

const sf::Vector2u Game::getViewportSize() {
    return {get().m_game_settings.data["viewport"]["width"],
            get().m_game_settings.data["viewport"]["height"]};
}

const sf::RenderWindow& Game::getRenderWindow() { return get().m_window; }

void Game::updateViewportSize() {
    sf::Vector2f viewportScale = scaleToFit(get().m_view.getSize(), getWindowSize());
    get().m_view.setViewport(sf::FloatRect(
        sf::Vector2f(0.5f - viewportScale.x / 2, 0.5f - viewportScale.y / 2), viewportScale));
    get().m_window.setView(get().m_view);
}

sf::Vector2f Game::getMousePos() {
    return getRenderWindow().mapPixelToCoords(sf::Mouse::getPosition(getRenderWindow()));
}

sf::Font* Game::getFont() { return &get().m_font; }

sf::View* Game::getView() { return &get().m_view; }

void Game::setCameraCenter(const sf::Vector2f& pos) {
    get().m_view.setCenter(pos);
    get().m_window.setView(get().m_view);
    // polsrodek
    get().m_fps_label.setPosition(
        pos - sf::Vector2f(384 / 2, 216 / 2) +
        sf::Vector2f(float(get().m_game_settings.data["viewport"]["width"]) - 1, 1));  // a
}
