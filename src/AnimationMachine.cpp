#include "AnimationMachine.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include <cassert>
#include <sys/types.h>

AnimationMachine::AnimationMachine(Texture::ID textureID, sf::Time duration, bool loop)
        : id(textureID), sheet(TextureHolder::instance().get(id)), duration(duration), loop(loop) {}

void AnimationMachine::update(sf::Time dt) {
    if (elapsedTime < duration) {
        elapsedTime += dt;
        if (loop && elapsedTime >= duration) {
            elapsedTime = sf::Time::Zero;
        }
    }
}
//#include <iostream>
void AnimationMachine::getSprite(unsigned i, sf::Sprite &sprite) const {
    //std::cout << i << "\n";
    i = std::min(i, sheet.get().spriteCount - 1);
    
    int col = i / sheet.get().textureRow;
    int row = i - col * sheet.get().textureRow;
    auto subRect =
            sf::IntRect(col * sheet.get().spriteSize.x, row * sheet.get().spriteSize.y, sheet.get().spriteSize.x,
                        sheet.get().spriteSize.y);
    sf::Drawable& tmp = sprite;

    sprite.setTexture(*sheet.get().texture, true);
    sprite.setTextureRect(subRect);
}

void AnimationMachine::toSprite(sf::Sprite &sprite) const {
    auto frameTime = duration / (float) sheet.get().spriteCount;
    getSprite(elapsedTime / frameTime, sprite);
}

bool AnimationMachine::isFinished() const {
    auto frameTime = duration / (float) sheet.get().spriteCount;
    return !loop && (elapsedTime / frameTime) >= sheet.get().spriteCount;
}

Texture::ID AnimationMachine::getID() const {
    return id;
}
