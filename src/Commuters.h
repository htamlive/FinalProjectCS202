#pragma once

#include "Entity.h"
#include "Light.h"
#include "Obstacle.h"
#include "PlayerState.h"

class Enemy : public virtual PlayerCollidable {
protected:
    void onStartPlayerCollision() override;

public:
    using PlayerCollidable::PlayerCollidable;

    Category::Type getCategory() const override;
};

class Animal : public Enemy {
public:
    using Enemy::Enemy;
};

class Vehicle : public Enemy, public Obstacle, public LightObserver {
private:
    void onStartPlayerCollision() override;

public:
    using Enemy::Enemy;

    void onLightChanged() override;

    Category::Type getCategory() const override;

private:
    sf::Vector2f tmpVelocity = {0, 0};
};

class Wood : public PlayerCollidable {
private:
    void onStartPlayerCollision() override;

    void onEndPlayerCollision() override;

public:
    using PlayerCollidable::PlayerCollidable;

    Category::Type getCategory() const override;
};