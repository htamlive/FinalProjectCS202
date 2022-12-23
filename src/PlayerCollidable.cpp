#include "PlayerCollidable.h"

void PlayerCollidable::onPlayerCollision(Player &player) {
    if (this->player == &player) {
        onRepeatPlayerCollision();
    } else {
        this->player = &player;
        onStartPlayerCollision();
    }
    isCollidingWithPlayer = true;
}

void PlayerCollidable::onStartPlayerCollision() {}

void PlayerCollidable::onRepeatPlayerCollision() {}

void PlayerCollidable::onEndPlayerCollision() {}

void PlayerCollidable::updateCurrent(sf::Time dt) {
    if (!isCollidingWithPlayer && this->player) {
        onEndPlayerCollision();
        this->player = nullptr;
    }
    isCollidingWithPlayer = false;
}