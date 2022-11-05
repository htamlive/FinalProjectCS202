#pragma once

#include "Entity.h"

class TrafficLight : public Entity {
public:
    TrafficLight();

    TrafficLight(float x, float y, float w, float h);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void updateCurrent(sf::Time dt) override;
};