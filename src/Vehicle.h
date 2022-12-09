#pragma once

#include "Entity.h"

class Vehicle : public Entity {
    using Entity::Entity;
public:

    void onLightChanged();

private:
    sf::Vector2f tmpVelocity = {0, 0};
};