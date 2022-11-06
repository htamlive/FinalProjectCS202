#pragma once

#include "Entity.h"

// TODO: how to change light?
class TrafficLight : public Entity {
public:
    TrafficLight() = default;

    TrafficLight(float x, float y, float w, float h);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;
};