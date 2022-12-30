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

void HealthBoost::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void HealthBoost::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::HealthBoost));
}

HealthBoost::HealthBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::HealthBoost, pos, size, {0, 0}, {}, false) {}

Category::Type HealthBoost::getCategory() const {
    return Category::HealthBoost;
}

std::string HealthBoost::getClassName() const {
    return "HealthBoost";
}

void SpeedBoost::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void SpeedBoost::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::SpeedBoost));
}

SpeedBoost::SpeedBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::SpeedBoost, pos, size, {0, 0}, {}, false) {}

Category::Type SpeedBoost::getCategory() const {
    return Category::SpeedBoost;
}

std::string SpeedBoost::getClassName() const {
    return "SpeedBoost";
}

void SmallSizeBoost::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void SmallSizeBoost::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::SmallSizeBoost));
}

SmallSizeBoost::SmallSizeBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::SmallSizeBoost, pos, size, {0, 0}, {}, false) {}

Category::Type SmallSizeBoost::getCategory() const {
    return Category::SmallSizeBoost;
}

std::string SmallSizeBoost::getClassName() const {
    return "SmallSizeBoost";
}

void InvincibleBoost::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void InvincibleBoost::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::InvincibleBoost));
}

InvincibleBoost::InvincibleBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::InvincibleBoost, pos, size, {0, 0}, {}, false) {}

Category::Type InvincibleBoost::getCategory() const {
    return Category::InvincibleBoost;
}

std::string InvincibleBoost::getClassName() const {
    return "InvincibleBoost";
}