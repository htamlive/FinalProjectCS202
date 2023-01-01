#include "Pickups.h"

void HealthPickup::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void HealthPickup::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::HealthBoost));
}

HealthPickup::HealthPickup(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::HealthBoost, pos, size, {0, 0}, {}, false) {}

Category::Type HealthPickup::getCategory() const {
    return Category::HealthPickup;
}

std::string HealthPickup::getClassName() const {
    return "HealthPickup";
}

bool HealthPickup::shouldSave() const {
    return true;
}

void SpeedPickup::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void SpeedPickup::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::SpeedBoost));
}

SpeedPickup::SpeedPickup(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::SpeedBoost, pos, size, {0, 0}, {}, false) {}

Category::Type SpeedPickup::getCategory() const {
    return Category::SpeedPickup;
}

std::string SpeedPickup::getClassName() const {
    return "SpeedPickup";
}

bool SpeedPickup::shouldSave() const {
    return true;
}

void SmallSizePickup::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void SmallSizePickup::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::SmallSizeBoost));
}

SmallSizePickup::SmallSizePickup(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::SmallSizeBoost, pos, size, {0, 0}, {}, false) {}

Category::Type SmallSizePickup::getCategory() const {
    return Category::SmallSizePickup;
}

std::string SmallSizePickup::getClassName() const {
    return "SmallSizePickup";
}

bool SmallSizePickup::shouldSave() const {
    return true;
}

void InvinciblePickup::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void InvinciblePickup::onStartPlayerCollision() {
    player->addEffect(EffectFactory::create(EffectType::InvincibleBoost));
}

InvinciblePickup::InvinciblePickup(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::InvincibleBoost, pos, size, {0, 0}, {}, false) {}

Category::Type InvinciblePickup::getCategory() const {
    return Category::InvinciblePickup;
}

std::string InvinciblePickup::getClassName() const {
    return "InvinciblePickup";
}

bool InvinciblePickup::shouldSave() const {
    return true;
}
