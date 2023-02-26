#include <ResourceManager/ResourceManager.hpp>

ResourceManager& ResourceManager::get() {
    static ResourceManager instance;
    return instance;
}

sf::Texture& ResourceManager::IgetTexture(const std::string path) {
    ResourceManager& resourceManager = get();
    if (!resourceManager.m_textures.contains(path)) {
        resourceManager.m_textures[path] = sf::Texture();
        resourceManager.m_textures[path].loadFromFile(path);
        resourceManager.m_textures[path].setSmooth(true);
    }
    return resourceManager.m_textures[path];
}

const sf::Texture& ResourceManager::getTexture(const std::string path) {
    return get().IgetTexture(path);
}

void ResourceManager::setTextureSmooth(const std::string path, bool smooth) {
    get().IgetTexture(path).setSmooth(smooth);
}
