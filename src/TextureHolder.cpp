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
            std::move(texture), spriteCount, spriteSize, textureRow});
    } else {
        std::cerr << "Loading texture from \"" << filename << "\" failed.\n";
        assert(0);
    }
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    auto found = textures.find(id);
    if (found == textures.end()) {
        std::cerr << "TextureHolder::getTexture: Texture not found.\n";
        assert(0);
    }
    return found->second.get()->texture;
}

SpriteSheet const &TextureHolder::get(Texture::ID id) const {
    
    auto found = textures.find(id);
    if (found == textures.end()) {
        std::cerr << "TextureHolder::get: Texture not found.\n";
        assert(0);
    }
    return *found->second;
}
