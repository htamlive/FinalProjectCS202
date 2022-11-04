#pragma once

#include "Enums.h"
#include "SceneNode.h"
#include "SpriteStage.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

/**
 * This is an abstract class for Entity in a scene such as car, human, ...
 * Override `drawCurrent` and `updateCurrent` to implement the concrete class
 */

class Entity : public SceneNode {
  private:
    sf::Vector2f velocity;

  protected:
    SpriteStage spriteStage;

  public:
    Entity() = default;

    Entity(Texture::ID type, sf::Vector2f velocity, float x, float y, float w,
           float h);

    const sf::Vector2f getVelocity() const;
    sf::Vector2f getVelocity();

    void setVelocity(sf::Vector2f velocity);
};
