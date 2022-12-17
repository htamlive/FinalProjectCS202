#pragma once

#include "Entity.h"
#include "Light.h"

class Animal : public Entity {
    using Entity::Entity;

    Category::Type getCategory() const override;
};

class Vehicle : public Entity, public LightObserver {
public:
    using Entity::Entity;

    void onLightChanged() override;

    Category::Type getCategory() const override;

private:
    sf::Vector2f tmpVelocity = {0, 0};
};

class Wood : public Entity {
    using Entity::Entity;

    Category::Type getCategory() const override;
};