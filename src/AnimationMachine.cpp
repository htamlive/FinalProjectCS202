#include "AnimationMachine.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

AnimationMachine::AnimationMachine(Texture::ID textureID, sf::Time duration,
                                   bool loop)
    : id(textureID), duration(duration), loop(loop) {}

void AnimationMachine::update(sf::Time dt) {
    if (elapsedTime < duration) {
        elapsedTime += dt;
        if (loop && elapsedTime >= duration) {
            elapsedTime = sf::Time::Zero;
        }
    }
}

sf::Sprite AnimationMachine::getSprite(unsigned i) const {
    auto &sheet = getSheet();
    sf::Sprite sprite;
    i = std::min(i, sheet.spriteCount - 1);
    int col = i / sheet.textureRow;
    int row = i - col * sheet.textureRow;
    auto subRect =
        sf::IntRect(col * sheet.spriteSize.x, row * sheet.spriteSize.y,
                    sheet.spriteSize.x, sheet.spriteSize.y);

    sprite.setTexture(sheet.texture, true);
    sprite.setTextureRect(subRect);

    return sprite;
}

sf::Sprite AnimationMachine::toSprite() const {
    auto &sheet = getSheet();
    auto frameTime = duration / (float)sheet.spriteCount;
    sf::Sprite sprite = getSprite(elapsedTime / frameTime);
    return sprite;
}

bool AnimationMachine::isFinished() const {
    auto &sheet = getSheet();
    auto frameTime = duration / (float)sheet.spriteCount;
    return !loop && (int)(elapsedTime / frameTime) >= sheet.spriteCount;
}

Texture::ID AnimationMachine::getID() const { return id; }

SpriteSheet const &AnimationMachine::getSheet() const {
    return TextureHolder::instance().get(id);
}
