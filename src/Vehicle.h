#pragma once

#include "Entity.h"

class Vehicle : public Entity {
public:
    Vehicle();

    Vehicle(sf::Vector2f velocity, float x, float y, float w, float h);

    void onLightChanged();

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void updateCurrent(sf::Time dt) override;

    bool stop;
};