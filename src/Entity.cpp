#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity()
    : animation(Texture::ID::LeftVehicle, DEF_ANIMATION_DURATION, true), size(0, 0) {}

Entity::Entity(Texture::ID texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity,
               sf::Time animationDuration, bool loop)
        : animation(texture, animationDuration, loop), velocity(velocity), size(size) {
    setPosition(position);
}


sf::Vector2f Entity::getVelocity() const { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

sf::FloatRect Entity::getBoundingRect() const {
    return {getAbsPosition().x, getAbsPosition().y, size.x, size.y};
}

void Entity::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    animation.update(dt);
}

void Entity::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates state) const {
    sf::Sprite sprite = animation.toSprite();
    auto scale = sprite.getScale();
    scale.x *= size.x / sprite.getLocalBounds().width;
    scale.y *= size.y / sprite.getLocalBounds().height;
    sprite.setScale(scale);
    target.draw(sprite, state);
}

bool Entity::isOutOfScreen() const {
    sf::FloatRect rect = getBoundingRect();
    sf::FloatRect screen = {0, 0, (float)WINDOW_VIDEO_MODE.width,
                            (float)WINDOW_VIDEO_MODE.height};
    return !screen.intersects(rect);
}