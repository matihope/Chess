#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class ResourceManager {
    private:
        ResourceManager() {};
        static ResourceManager& get();
        sf::Texture& IgetTexture(const std::string path);
        std::map<std::string, sf::Texture> m_textures;

    public:
        ResourceManager(const ResourceManager&) = delete;
        static const sf::Texture& getTexture(const std::string path);
        static void setTextureSmooth(const std::string path, bool smooth);
};
