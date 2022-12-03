#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity()
    : animation(Texture::ID::LeftVehicle, DEF_ANIMATION_DURATION, true), width(0),
      height(0) {}

Entity::Entity(sf::Vector2f velocity, float x, float y,
               float w, float h, Texture::ID type, sf::Time animationDuration, bool loop)
        : animation(type, animationDuration, loop), velocity(velocity), width(w), height(h) {
    setPosition({x, y});
}

sf::Vector2f Entity::getVelocity() const { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

sf::FloatRect Entity::getBoundingRect() const {
    return {getAbsPosition().x, getAbsPosition().y, width, height};
}

void Entity::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    animation.update(dt);
}

void Entity::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates state) const {
    sf::Sprite sprite = animation.toSprite();
    auto scale = sprite.getScale();
    scale.x *= width / sprite.getLocalBounds().width;
    scale.y *= height / sprite.getLocalBounds().height;
    sprite.setScale(scale);
    target.draw(sprite, state);
}

bool Entity::isOutOfScreen() const {
    sf::FloatRect rect = getBoundingRect();
    sf::FloatRect screen = {0, 0, (float)WINDOW_VIDEO_MODE.width,
                            (float)WINDOW_VIDEO_MODE.height};
    return !screen.intersects(rect);
}
