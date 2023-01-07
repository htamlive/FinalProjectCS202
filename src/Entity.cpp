#include "Entity.h"
#include "Consts.h"
#include "Enums.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

Entity::Entity()
        : animation(Texture::Null, DEF_ANIMATION_DURATION, true), localBounds(0, 0, 0, 0) {}

Entity::Entity(Texture::ID texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity,
               sf::Time animationDuration, bool loop)
        : animation(texture, animationDuration, loop), velocity(velocity), spriteBounds({0, 0}, size) {
    setPosition(position);
    localBounds = spriteBounds;
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
    auto bounds = getSpriteBounds();
    auto preScale = sprite.getScale();
    sprite.setScale(bounds.width / sprite.getLocalBounds().width * preScale.x,
                    bounds.height / sprite.getLocalBounds().height * preScale.y);
    sprite.setPosition(bounds.left, bounds.top);
    target.draw(sprite, state);
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
    out << velocity.x/SYSTEM_SCALE << " " << velocity.y/SYSTEM_SCALE << std::endl;
    out << localBounds.left/SYSTEM_SCALE << " " << localBounds.top / SYSTEM_SCALE << " " << localBounds.width / SYSTEM_SCALE << " " << localBounds.height / SYSTEM_SCALE << std::endl;
    out << spriteBounds.left / SYSTEM_SCALE << " " << spriteBounds.top / SYSTEM_SCALE << " " << spriteBounds.width / SYSTEM_SCALE << " " << spriteBounds.height / SYSTEM_SCALE << std::endl;
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
    spriteBounds = {spriteBoundsLeft*SYSTEM_SCALE, spriteBoundsTop * SYSTEM_SCALE, spriteBoundsWidth * SYSTEM_SCALE, spriteBoundsHeight * SYSTEM_SCALE };
    localBounds = {localBoundsLeft * SYSTEM_SCALE, localBoundsTop * SYSTEM_SCALE, localBoundsWidth * SYSTEM_SCALE, localBoundsHeight * SYSTEM_SCALE };
    velocity = {velocityX, velocityY};
    velocity *= SYSTEM_SCALE;
    animation.load(in);
}

std::string Entity::getClassName() const {
    return "Entity";
}

sf::FloatRect Entity::getSpriteBounds() const {
    return spriteBounds;
}
