#pragma once

#include "AnimationMachine.h"
#include "Enums.h"
#include "SceneNode.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * This is a class for Entity in a scene such as car, human,...
 * Override `drawCurrent` and `updateCurrent` if need to.
 */

class Entity : public SceneNode {
private:
    sf::Vector2f velocity;
    sf::FloatRect localBounds;
    sf::FloatRect spriteBounds;

protected:
    AnimationMachine animation;

public:
    Entity();
    Entity(Texture::ID texture, sf::Vector2f velocity,
           sf::Time animationDuration = DEF_ANIMATION_DURATION,
           bool loop = true);
    Entity(Texture::ID texture, sf::Vector2f position, sf::Vector2f size, sf::Vector2f velocity,
           sf::Time animationDuration = DEF_ANIMATION_DURATION,
           bool loop = true);
    Entity(Texture::ID texture, sf::FloatRect boundRect, sf::Vector2f velocity,
           sf::Time animationDuration = DEF_ANIMATION_DURATION,
           bool loop = true);

    /**
     * Check if this entity is out of screen
     * @return true if out of screen, false otherwise
     */
    bool isOutOfScreen() const;

    sf::Vector2f getVelocity() const;

    /**
     * Set the velocity
     *
     * @param velocity New velocity
     */
    void setVelocity(sf::Vector2f velocity);

    /**
     * @return the bounding rectangle of the Entity
     */
    sf::FloatRect getLocalBounds() const override;

    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates state) const override;

    /**
     * Update the Entity, can be extended in derived class. Default
     * implementation only updates the position according to velocity &
     * animation.
     *
     * @param dt time since last frame
     */
    void updateCurrent(sf::Time dt) override;
    
    void adjustSpriteBounds(float offX, float offY);
    void adjustBounds(float offX, float offY, float cropWidth, float cropHeight);

    Category getCategory() const override;
};
