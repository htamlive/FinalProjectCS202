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
        if (!spriteSize.x || !spriteSize.y) {
            spriteSize = texture.getSize();
            spriteCount = 1;
        }
        if (textureRow == 0) {
            textureRow = texture.getSize().x / spriteSize.x;
        }
        sheets[id] = std::make_unique<TextureSheet>(std::move(texture), spriteCount, spriteSize, textureRow);
    } else {
        throw std::runtime_error("TextureHolder::load - Failed to load " +
                                 filename);
    }
}

void TextureHolder::add(Texture::ID id, const SpriteSheet& sheet) {
    sheets[id] = std::make_unique<SpriteSheet>(sheet);
}

Sheet const &TextureHolder::getSheet(Texture::ID id) const {
    auto found = sheets.find(id);
    if (found == sheets.end()) {
        std::cerr << "TextureHolder::getSheet: Sheet not found.\n";
        assert(0);
    }
    return *found->second;
}

sf::Texture const &TextureHolder::getTexture(Texture::ID id) const {
    return getSheet(id).getTexture();
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

TextureSheet::TextureSheet(const sf::Texture& texture, unsigned int spriteCount, sf::Vector2u spriteSize,
                           unsigned int textureRow) : texture(texture), spriteCount(spriteCount),
                                                      spriteSize(spriteSize), textureRow(textureRow) {}

unsigned int SpriteSheet::getCount() const {
    return endIdx - startIdx + 1;
}

sf::Texture const &SpriteSheet::getTexture() const {
    return TextureHolder::instance().getTexture(texture);
}

sf::Sprite SpriteSheet::getSprite(unsigned int i) const {
    auto &textureSheet = TextureHolder::instance().getSheet(texture);
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
