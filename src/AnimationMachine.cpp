#include "AnimationMachine.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <cassert>
#include <iostream>
#include <sys/types.h>

AnimationMachine::AnimationMachine(sf::Sprite &sprite, sf::Texture &texture,
                                   u_int spriteCount, sf::Time duration,
                                   u_int spriteSize, u_int textureRow)
    : texture(texture), sprite(sprite), spriteCount(spriteCount),
      textureRow(textureRow), spriteSize(spriteSize), duration(duration) {}

void AnimationMachine::updateAnimation(sf::Time dt) {
    elaspedTime += dt;
    sf::Time frameTime = duration / (float)spriteCount;
    if (elaspedTime > duration) {
        elaspedTime = sf::Time::Zero;
    }

    sprite = getSprite(elaspedTime / frameTime);
}

sf::Sprite AnimationMachine::getSprite(u_int i) {
    assert(i <= spriteCount);
    int row = i / textureRow;
    int col = i - row * textureRow;
    auto subRect =
        sf::IntRect(row * spriteSize, col * spriteSize, spriteSize, spriteSize);

    sf::Sprite sp;
    sp.setTexture(texture);
    sp.setTextureRect(subRect);

    return sp;
}
