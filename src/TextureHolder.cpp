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

void TextureHolder::load(Texture::ID id, const std::string &filename,
                         sf::Vector2u spriteSize, unsigned int spriteCount,
                         unsigned int textureRow) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        if (!spriteSize.x || !spriteSize.y)
            spriteSize = texture.getSize();
        textures[id] = std::make_unique<TextureSheet>(
                texture, spriteCount, spriteSize, textureRow);
        sprites[id] = {id};
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
    return found->second->getTexture();
}

void TextureHolder::addSprite(Texture::ID id, const SpriteSheet &info) {
    sprites[id] = info;
}

SpriteSheet const &TextureHolder::getSpriteSheet(Texture::ID id) const {
    auto found = sprites.find(id);
    if (found == sprites.end()) {
        std::cerr << "TextureHolder::getSpriteSheet: Sheet not found.\n";
        assert(0);
    }
    return found->second;
}

TextureSheet const &TextureHolder::getTextureSheet(Texture::ID id) const {
    auto found = textures.find(id);
    if (found == textures.end()) {
        std::cerr << "TextureHolder::getTextureSheet: Sheet not found.\n";
        assert(0);
    }
    return *found->second;
}

sf::Sprite TextureSheet::getSprite(unsigned int i) const {
    int row = i / textureRow;
    int col = i - row * textureRow;
    auto subRect =
            sf::IntRect(col * spriteSize.x, row * spriteSize.y,
                        spriteSize.x, spriteSize.y);

    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sprite.setTextureRect(subRect);

    return sprite;
}

unsigned int TextureSheet::getCount() const {
    return spriteCount;
}

sf::Texture const &TextureSheet::getTexture() const {
    return texture;
}

TextureSheet::TextureSheet(const sf::Texture &texture, unsigned int spriteCount, sf::Vector2u spriteSize,
                           unsigned int textureRow) : texture(texture), spriteCount(spriteCount),
                                                      spriteSize(spriteSize), textureRow(textureRow) {}

unsigned int SpriteSheet::getCount() const {
    return endIdx - startIdx + 1;
}

sf::Texture const &SpriteSheet::getTexture() const {
    return TextureHolder::instance().getTexture(texture);
}

sf::Sprite SpriteSheet::getSprite(unsigned int i) const {
    auto &textureSheet = TextureHolder::instance().getTextureSheet(texture);
    auto sprite = textureSheet.getSprite(startIdx + i);
    sf::Vector2f scale = {1, 1};
    if (mirrorVertical) scale.x *= -1;
    if (mirrorHorizontal) scale.y *= -1;
    sprite.setScale(sprite.getScale().x * scale.x, sprite.getScale().y * scale.y);
    return sprite;
}

SpriteSheet::SpriteSheet(Texture::ID id) : texture(id) {}

SpriteSheet::SpriteSheet(Texture::ID id, bool mirrorVertical, bool mirrorHorizontal) : texture(id),
                                                                                       mirrorVertical(mirrorVertical),
                                                                                       mirrorHorizontal(mirrorHorizontal) {}

SpriteSheet::SpriteSheet(Texture::ID id, unsigned int startIdx, unsigned int endIdx, bool mirrorVertical,
                         bool mirrorHorizontal) : texture(id), startIdx(startIdx), endIdx(endIdx),
                                                  mirrorHorizontal(mirrorHorizontal), mirrorVertical(mirrorVertical) {}

SpriteSheet::SpriteSheet(Texture::ID id, unsigned int index, bool mirrorVertical, bool mirrorHorizontal) : texture(id),
                                                                                                           startIdx(index),
                                                                                                           endIdx(index),
                                                                                                           mirrorHorizontal(mirrorHorizontal),
                                                                                                           mirrorVertical(mirrorVertical) {}
