#include <ResourceManager/ResourceManager.hpp>

ResourceManager &ResourceManager::get() {
  static ResourceManager instance;
  return instance;
}

sf::Texture &ResourceManager::getMutTexture(const std::string &path) {
  if (!m_textures.contains(path)) {
    m_textures[path] = sf::Texture();
    m_textures[path].loadFromFile(path);
  }
  return m_textures[path];
}

const sf::Texture &ResourceManager::getTexture(const std::string &path) {
  return getMutTexture(path);
}

void ResourceManager::setTextureSmooth(const std::string &path, bool smooth) {
  getMutTexture(path).setSmooth(smooth);
}
