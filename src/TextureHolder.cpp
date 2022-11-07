#include <iostream>

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
    if (texture->loadFromFile(filename)) {
        if (!spriteSize.x || !spriteSize.y)
            spriteSize = texture->getSize();
        textures[type] = {std::move(texture), spriteCount, spriteSize, textureRow};
    } else {
        std::cerr << "Loading texture from \"" << filename << "\" failed.\n";
    }
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    auto found = textures.find(id);
    return *found->second.texture;
}

SpriteSheet const &TextureHolder::get(Texture::ID id) const {
    auto found = textures.find(id);
    return found->second;
}
