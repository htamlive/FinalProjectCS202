#pragma once

#include "Entity.h"
#include "Light.h"

class Vehicle : public Entity, public LightObserver {
    using Entity::Entity;
public:

    void onLightChanged() override;

private:
    sf::Vector2f tmpVelocity = {0, 0};
};