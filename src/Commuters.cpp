#include "Commuters.h"
#include "Consts.h"
#include "TextureHolder.h"

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}

Category::Type Vehicle::getCategory() const {
    if (getVelocity() != sf::Vector2f(0, 0)) {
        return Enemy::getCategory();
    }
    else
        return Obstacle::getCategory();
}

void Vehicle::onStartPlayerCollision() {
    if (getCategory() == Enemy::getCategory()) {
        Enemy::onStartPlayerCollision();
    }
    else if (getCategory() == Obstacle::getCategory()) {
        Obstacle::onStartPlayerCollision();
    }
}

Category::Type Wood::getCategory() const {
    return Category::Wood;
}

void Wood::onStartPlayerCollision() {
    player->addPlatformVelocity(getVelocity());
}

void Wood::onEndPlayerCollision() {
    player->addPlatformVelocity(-getVelocity());
}

Category::Type Enemy::getCategory() const {
    return Category::Enemy;
}

void Enemy::onStartPlayerCollision() {
    auto getDirection = [](sf::Vector2f v) {
        if (v.y != 0) {
            v.y /= std::abs(v.y);
        }
        if (v.x != 0) {
            v.x /= std::abs(v.x);
        }
        return v;
    };

    if (!player->isInvincible()) {
        player->takeDamage();
        sf::Vector2f direction = getAbsPosition() - player->getAbsPosition();
        if (abs(direction.x) > abs(direction.y)) {
            direction.y = 0;
        } else {
            direction.x = 0;
        }
        direction = -getDirection(direction);
        sf::Vector2f newPos = player->getPosition() + direction * (GRID_SIZE.x / 2);
        player->setState(new CollidingState(player, newPos));
    }
}
