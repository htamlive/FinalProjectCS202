#include "Entity.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

Entity::Entity(Texture::ID type, sf::Vector2f velocity, float x, float y,
               float w, float h)
    : spriteStage(type), velocity(velocity) {}

const sf::Vector2f Entity::getVelocity() const { return velocity; }

sf::Vector2f Entity::getVelocity() { return velocity; }

void Entity::setVelocity(sf::Vector2f _velocity) { velocity = _velocity; }
