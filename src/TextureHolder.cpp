#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <memory>
#include <cassert>

#include "TextureHolder.h"

TextureHolder &TextureHolder::instance() {
    static TextureHolder *ins = nullptr;
    if (ins == nullptr) {
        ins = new TextureHolder;
    }
    return *ins;
}

void TextureHolder::load(Texture::ID type, const std::string &filename,
                         sf::Vector2u spriteSize, unsigned int spriteCount,
                         unsigned int textureRow) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        if (!spriteSize.x || !spriteSize.y)
            spriteSize = texture.getSize();
        textures[type] = std::make_unique<SpriteSheet>(SpriteSheet{
            texture, spriteCount, spriteSize, textureRow});
    } else {
        throw std::runtime_error("TextureHolder::load - Failed to load " +
                                 filename);
    }
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    auto found = textures.find(id);
    if (found == textures.end()) {
        throw std::runtime_error("TextureHolder::getTexture - Failed to find " +
                                 std::to_string(id));
    }
    return found->second->texture;
}

SpriteSheet const &TextureHolder::get(Texture::ID id) const {
    
    auto found = textures.find(id);
    if (found == textures.end()) {
        throw std::runtime_error("TextureHolder::get - Failed to find " +
                                 std::to_string(id));
    }
    return *found->second;
}
