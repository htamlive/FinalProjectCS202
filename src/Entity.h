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

class Entity : public virtual SceneNode {
protected:
    sf::Vector2f velocity;
    sf::FloatRect localBounds;
    sf::FloatRect spriteBounds;
    AnimationMachine animation;

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

    virtual bool shouldSave() const override {
        return false;
    }

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

    sf::Vector2f getVelocity() const;

    /**
     * Set the velocity
     *
     * @param velocity New velocity
     */
    void setVelocity(sf::Vector2f velocity);

    sf::FloatRect getLocalBounds() const override;

    sf::FloatRect getSpriteBounds() const;

    /**
     * Does not account for scaling.
     */
    void adjustSpriteBounds(float offX, float offY);

    /**
     * Does not account for scaling.
     */
    void adjustBounds(float offX, float offY, float cropWidth, float cropHeight);

    std::string getClassName() const override;

    void saveCurrentNode(std::ostream& out = std::cout) const override;

    void loadCurrentNode(std::istream& in = std::cin) override;
};
