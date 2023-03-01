#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class ResourceManager {
    private:
        ResourceManager() {};
        sf::Texture& getMutTexture(const std::string path);
        std::map<std::string, sf::Texture> m_textures;

    public:
     // singleton stuff
     ResourceManager(const ResourceManager&) = delete;
     void operator=(const ResourceManager&) = delete;
     static ResourceManager& get();

     const sf::Texture& getTexture(const std::string path);
     void setTextureSmooth(const std::string path, bool smooth);
};
