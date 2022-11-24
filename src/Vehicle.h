#pragma once

#include "Entity.h"

class Vehicle : public Entity {
public:
    Vehicle();

    Vehicle(sf::Vector2f velocity, float x, float y, float w, float h);

    void onLightChanged();

private:
    sf::Vector2f tmp_velocity;
};