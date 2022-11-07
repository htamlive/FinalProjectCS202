#include "TextureHolder.h"

TextureHolder &TextureHolder::instance() {
    static TextureHolder *ins = nullptr;
    if (ins == nullptr) {
        ins = new TextureHolder;
    }
    return *ins;
}

void
TextureHolder::load(Texture::ID type, const std::string &filename, sf::Vector2u spriteSize, unsigned int spriteCount,
                    unsigned int textureRow) {
    std::unique_ptr<sf::Texture> texture{};
    texture->loadFromFile(filename);
    textures[type] = {std::move(texture), spriteCount, spriteSize, textureRow};
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    auto found = textures.find(id);
    return *found->second.texture;
}

SpriteSheet const &TextureHolder::get(Texture::ID id) const {
    auto found = textures.find(id);
    return found->second;
}
