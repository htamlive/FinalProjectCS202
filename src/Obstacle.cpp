#include "Obstacle.h"

void Obstacle::onStartPlayerCollision() {
    if (!player->isInvincible()) {
        sf::Vector2f direction = -player->getDirectionVec();
        auto newPos = player->getPosition() + direction * (GRID_SIZE.x / 2);
        player->setState(new ObstacleCollidingState(player, newPos));
    }
}

Category::Type Obstacle::getCategory() const {
    return Category::Obstacle;
}

std::string Obstacle::getClassName() const {
    return "Obstacle";
}

void Rock::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    Obstacle::updateCurrent(dt);
}

Rock::Rock(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::Obstacle, pos, size, {0, 0}, {}, false) {}

Category::Type Rock::getCategory() const {
    return Obstacle::getCategory();
}

std::string Rock::getClassName() const {
    return "Rock";
}

bool Rock::shouldSave() const {
    return true;
}