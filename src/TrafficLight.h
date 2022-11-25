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

    void changeLight();

    void changingPhase();

    sf::Time nextTime, currentTime, timer;

    std::pair<std::pair<Texture::ID, Texture::ID>, std::pair<Texture::ID, Texture::ID>> sprites = {{Texture::ID::GreenLight,
                                                                                                    Texture::ID::GreenToRed},
                                                                                                   {Texture::ID::RedLight,
                                                                                                    Texture::ID::RedToGreen}};

};