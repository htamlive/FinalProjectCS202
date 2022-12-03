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
    float width, height;

protected:
    AnimationMachine animation;

public:
    Entity();
    Entity(Texture::ID type, sf::Vector2f vel,
           sf::Time animation_duration = DEF_ANIMATION_DURATION,
           bool loop = true);
    Entity(sf::Vector2f velocity, float x, float y, float w, float h,
           Texture::ID type,
           sf::Time animation_duration = DEF_ANIMATION_DURATION,
           bool loop = true);
    Entity(sf::Vector2f velocity, sf::Vector2f pos, sf::Vector2f size,
           Texture::ID type,
           sf::Time animation_duration = DEF_ANIMATION_DURATION,
           bool loop = true);
    Entity(sf::Vector2f velocity, sf::FloatRect boundRect,
           Texture::ID type,
           sf::Time animation_duration = DEF_ANIMATION_DURATION,
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
    sf::FloatRect getBoundingRect() const override;

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
};
