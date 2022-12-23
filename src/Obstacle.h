#pragma once

#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include "Entity.h"
#include "TextureHolder.h"
#include "PlayerState.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Obstacle : public virtual PlayerCollidable {
protected:
    void onStartPlayerCollision() override {
        sf::Vector2f direction = -player->getDirectionVec();
        auto         newPos    = player->getPosition() + direction * (GRID_SIZE.x / 2);
        player->setState(new ObstacleCollidingState(player, newPos));
    }

public:
    Obstacle() = default;

    Obstacle(sf::Vector2f pos, sf::Vector2f size) : PlayerCollidable(Texture::ID::Obstacle, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Category::Obstacle;
    }
};

class HealthBoost : public PlayerCollidable {
public:
    HealthBoost(sf::Vector2f pos, sf::Vector2f size) : PlayerCollidable(Texture::ID::HealthBoost, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Category::HealthBoost;
    }

    void onStartPlayerCollision() override {
        player->addEffect(EffectFactory::create(EffectType::HealthBoost));
    }
};