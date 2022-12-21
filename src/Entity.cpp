#include "Entity.h"
#include "Consts.h"
#include "Enums.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

Entity::Entity()
        : animation(Texture::ID::LeftVehicle, DEF_ANIMATION_DURATION, true), localBounds(0, 0, 0, 0) {}

Entity::Entity(Texture::ID texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity,
               sf::Time animationDuration, bool loop)
        : animation(texture, animationDuration, loop), velocity(velocity), spriteBounds({0, 0}, size) {
    setPosition(position);
    localBounds = sf::FloatRect({0, 0}, {size.x, size.y});
}


sf::Vector2f Entity::getVelocity() const { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }

sf::FloatRect Entity::getLocalBounds() const {
    return localBounds;
}

void Entity::updateCurrent(sf::Time dt) {
    move(getVelocity() * dt.asSeconds());
    animation.update(dt);
}

void Entity::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates state) const {
    sf::Sprite sprite = animation.toSprite();
    auto scale = sprite.getScale();
    sprite.setScale(scale.x * spriteBounds.width / sprite.getLocalBounds().width,
                    scale.y * spriteBounds.height / sprite.getLocalBounds().height);
    sprite.setPosition(spriteBounds.left, spriteBounds.top);
    target.draw(sprite, state);
}

// TODO: this function is ugly
bool Entity::isOutOfScreen() const {
    return getAbsPosition().x + localBounds.width < 0 || getAbsPosition().x > WINDOW_VIDEO_MODE.width;
}

void Entity::adjustSpriteBounds(float offX, float offY) {
    spriteBounds.left += offX;
    spriteBounds.top += offY;
}

void Entity::adjustBounds(float offX, float offY, float cropWidth, float cropHeight) {
    localBounds.left += offX;
    localBounds.top += offY;
    localBounds.width -= cropWidth;
    localBounds.height -= cropHeight;
}


void Entity::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
    out << velocity.x << " " << velocity.y << std::endl;
    out << localBounds.left << " " << localBounds.top << " " << localBounds.width << " " << localBounds.height << std::endl;
    out << spriteBounds.left << " " << spriteBounds.top << " " << spriteBounds.width << " " << spriteBounds.height << std::endl;
    animation.save(out);
}

void Entity::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
    float velocityX, velocityY;
    float localBoundsLeft, localBoundsTop, localBoundsWidth, localBoundsHeight;
    float spriteBoundsLeft, spriteBoundsTop, spriteBoundsWidth, spriteBoundsHeight;
    in >> velocityX >> velocityY;
    in >> localBoundsLeft >> localBoundsTop >> localBoundsWidth >> localBoundsHeight;
    in >> spriteBoundsLeft >> spriteBoundsTop >> spriteBoundsWidth >> spriteBoundsHeight;
    spriteBounds = {spriteBoundsLeft, spriteBoundsTop, spriteBoundsWidth, spriteBoundsHeight};
    localBounds = {localBoundsLeft, localBoundsTop, localBoundsWidth, localBoundsHeight};
    velocity = {velocityX, velocityY};
    animation.load(in);
}

std::string Entity::getClassName() const {
    return "Entity";
}

