#pragma once

#include "Entity.h"

/**
 * Light always starts as green.
 */
class TrafficLight : public Entity {
public:
    TrafficLight() = default;

    TrafficLight(float x, float y, float w, float h, sf::Time greenTimer, sf::Time redTimer);

private:
    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void changeLight();

    sf::Time nextTime, currentTime, timer;

    std::pair<Texture::ID, Texture::ID> sprites = {Texture::ID::GreenLightSprite, Texture::ID::RedLightSprite};
};