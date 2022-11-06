#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity() : animation(Texture::ID::VehicleSprites) {}

Entity::Entity(Texture::ID type, sf::Vector2f velocity, float x, float y,
               float w, float h)
        : animation(type), velocity(velocity) {}

sf::Vector2f Entity::getVelocity() const { return velocity; }

sf::Vector2f &Entity::getVelocity() { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

sf::FloatRect Entity::getBoundingRect() const {
    return sf::FloatRect(getAbsPosition().x, getAbsPosition().y, 100.f, 100.f);
}

void Entity::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    animation.update(dt);
}