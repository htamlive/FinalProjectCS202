#pragma once

#include "Consts.h"
#include "Enums.h"
#include "SceneNode.h"
#include "Entity.h"
#include "TextureHolder.h"
#include "PlayerState.h"
#include "PlayerCollidable.h"

#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>

class Obstacle : public virtual PlayerCollidable {
protected:
    void onStartPlayerCollision() override {
        sf::Vector2f direction = -player->getDirectionVec();
        auto newPos = player->getPosition() + direction * (GRID_SIZE.x / 2);
        player->setState(new ObstacleCollidingState(player, newPos));
    }

public:
    using PlayerCollidable::PlayerCollidable;

    Category::Type getCategory() const override {
        return Category::Obstacle;
    }
};

class Rock : public virtual Obstacle, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override {
        Entity::updateCurrent(dt);
        Obstacle::updateCurrent(dt);
    }

public:
    Rock(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::Obstacle, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Obstacle::getCategory();
    }
};

class HealthBoost : public virtual PlayerCollidable, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override {
        Entity::updateCurrent(dt);
        PlayerCollidable::updateCurrent(dt);
    }

    void onStartPlayerCollision() override {
        player->addEffect(EffectFactory::create(EffectType::HealthBoost));
    }

public:
    HealthBoost(sf::Vector2f pos, sf::Vector2f size) : Entity(Texture::ID::HealthBoost, pos, size, {0, 0}, {}, false) {}

    Category::Type getCategory() const override {
        return Category::HealthBoost;
    }
};