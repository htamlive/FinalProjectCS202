#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include "Entity.h"
#include "TextureHolder.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Obstacle : public Entity {
public:
    Obstacle(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::Obstacle, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Category::Obstacle;
    }
};

class HealthBoost : public Entity {
public:
    HealthBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::HealthBoost, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Category::HealthBoost;
    }
};