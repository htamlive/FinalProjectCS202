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

class Animal : public virtual Enemy, public virtual Entity {
private:
    void updateCurrent(sf::Time dt) override;

public:
    using Entity::Entity;
};

class Vehicle : public virtual Enemy, public virtual Obstacle, public virtual Entity, public LightObserver {
private:
    void onStartPlayerCollision() override;

    void updateCurrent(sf::Time dt) override;
public:
    using Entity::Entity;

    void onLightChanged() override;

    Category::Type getCategory() const override;

private:
    sf::Vector2f tmpVelocity = {0, 0};
};

class Wood : public virtual PlayerCollidable, public virtual Entity {
private:
    void onStartPlayerCollision() override;

    void onEndPlayerCollision() override;

    void updateCurrent(sf::Time dt) override;

public:
    using Entity::Entity;

    Category::Type getCategory() const override;
};