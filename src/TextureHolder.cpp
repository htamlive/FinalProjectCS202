#include <SFML/Graphics/Texture.hpp>
#include <cassert>
#include <iostream>
#include <memory>

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
                         unsigned int texturePerRow) {
    sf::Texture texture;
    if (texture.loadFromFile(filename)) {
        if (!spriteSize.x || !spriteSize.y) {
            spriteSize = texture.getSize();
            spriteCount = 1;
        }
        if (texturePerRow == 0) {
            texturePerRow = texture.getSize().x / spriteSize.x;
        }
        sheets[id] = std::make_unique<TextureSheet>(
            std::move(texture), spriteCount, spriteSize, texturePerRow);
    } else {
        throw std::runtime_error("TextureHolder::load - Failed to load " +
                                 filename);
    }
}

void TextureHolder::add(Texture::ID id, const SpriteSheet &sheet) {
    sheets[id] = std::make_unique<SpriteSheet>(sheet);
}

Sheet const &TextureHolder::getSheet(Texture::ID id) const {
    auto found = sheets.find(id);
    if (found == sheets.end()) {
        throw std::runtime_error("TextureHolder::getSheet(" +
                                 std::to_string(id) + "): Sheet not found.\n");
    }
    return *found->second;
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    return getSheet(id).getTexture();
}

sf::Sprite TextureSheet::getSprite(unsigned int i) const {
    int row = i / texturePerRow;
    int col = i - row * texturePerRow;
    auto subRect = sf::IntRect(col * spriteSize.x, row * spriteSize.y,
                               spriteSize.x, spriteSize.y);

    sf::Sprite sprite;
    sprite.setTexture(texture, true);
    sprite.setTextureRect(subRect);

    return sprite;
}

unsigned int TextureSheet::getCount() const { return spriteCount; }

sf::Texture const &TextureSheet::getTexture() const { return texture; }

TextureSheet::TextureSheet(const sf::Texture &texture, unsigned int spriteCount,
                           sf::Vector2u spriteSize, unsigned int texturePerRow)
    : texture(texture), spriteCount(spriteCount), spriteSize(spriteSize),
      texturePerRow(texturePerRow) {}

unsigned int SpriteSheet::getCount() const { return endIdx - startIdx + 1; }

sf::Texture const &SpriteSheet::getTexture() const {
    return TextureHolder::instance().getTexture(texture);
}

sf::Sprite SpriteSheet::getSprite(unsigned int i) const {
    auto &textureSheet = TextureHolder::instance().getSheet(texture);
    auto sprite = textureSheet.getSprite(startIdx + i);
    sf::Vector2f scale = sprite.getScale();
    if (mirrorVertical)
        scale.x *= -1;
    if (mirrorHorizontal)
        scale.y *= -1;
    sprite.setScale(scale);
    auto offset =
        sf::Vector2f(mirrorVertical ? sprite.getGlobalBounds().width : 0,
                     mirrorHorizontal ? sprite.getGlobalBounds().height : 0);
    sprite.setOrigin(offset);
    return sprite;
}

SpriteSheet::SpriteSheet(Texture::ID id) : texture(id) {}

SpriteSheet::SpriteSheet(Texture::ID id, bool mirrorVertical,
                         bool mirrorHorizontal)
    : texture(id), mirrorVertical(mirrorVertical),
      mirrorHorizontal(mirrorHorizontal) {}

SpriteSheet::SpriteSheet(Texture::ID id, unsigned int startIdx,
                         unsigned int endIdx, bool mirrorVertical,
                         bool mirrorHorizontal)
    : texture(id), startIdx(startIdx), endIdx(endIdx),
      mirrorHorizontal(mirrorHorizontal), mirrorVertical(mirrorVertical) {}

SpriteSheet::SpriteSheet(Texture::ID id, unsigned int index,
                         bool mirrorVertical, bool mirrorHorizontal)
    : texture(id), startIdx(index), endIdx(index),
      mirrorHorizontal(mirrorHorizontal), mirrorVertical(mirrorVertical) {}
