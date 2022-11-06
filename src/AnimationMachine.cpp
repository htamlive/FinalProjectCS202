#include "AnimationMachine.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <cassert>
#include <sys/types.h>

AnimationMachine::AnimationMachine(Texture::ID textureID, sf::Time duration)
        : sheet(TextureHolder::instance().get(textureID)), duration(duration) {}

void AnimationMachine::update(sf::Time dt) {
    elapsedTime += dt;
    sf::Time frameTime = duration / (float) sheet.spriteCount;
    if (elapsedTime > duration) {
        elapsedTime = sf::Time::Zero;
    }
}

void AnimationMachine::getSprite(u_int i, sf::Sprite &sprite) const {
    assert(i <= sheet.spriteCount);
    int row = i / sheet.textureRow;
    int col = i - row * sheet.textureRow;
    auto subRect =
            sf::IntRect(row * sheet.spriteSize, col * sheet.spriteSize, sheet.spriteSize, sheet.spriteSize);

    sprite.setTexture(*sheet.texture, true);
    sprite.setTextureRect(subRect);
}

void AnimationMachine::toSprite(sf::Sprite &sprite) const {
    auto frameTime = duration / (float) sheet.spriteCount;
    getSprite(elapsedTime / frameTime, sprite);
}
