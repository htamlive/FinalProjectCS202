#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity() : animation(Texture::ID::Vehicle, DEF_ANIMATION_DURATION, true), width(0), height(0) {}

Entity::Entity(sf::Vector2f velocity, float x, float y,
               float w, float h, Texture::ID type, sf::Time animation_duration, bool loop)
        : animation(type, animation_duration, loop), velocity(velocity), width(w), height(h) {
    setPosition({x, y});
}

sf::Vector2f Entity::getVelocity() const { return velocity; }

sf::Vector2f &Entity::getVelocity() { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

sf::FloatRect Entity::getBoundingRect() const {
    return {getAbsPosition().x, getAbsPosition().y, width, height};
}

void Entity::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    animation.update(dt);
}

void Entity::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    sf::Sprite sprite = animation.toSprite();
    target.draw(sprite, state);
}
