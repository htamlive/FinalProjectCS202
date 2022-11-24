#include "TrafficLight.h"
#include "TextureHolder.h"
#include "Consts.h"

void TrafficLight::updateCurrent(sf::Time dt) {
    timer += dt;
    if (timer >= currentTime)
        changeLight();

    Entity::updateCurrent(dt);
}

void TrafficLight::changeLight() {
    std::swap(currentTime, nextTime);
    timer = sf::Time::Zero;

    std::swap(sprites.first, sprites.second);
    animation = AnimationMachine(sprites.first, {}, false);

    // TODO: Signal light changing to vehicles
}

TrafficLight::TrafficLight(float x, float y, float w, float h, sf::Time greenTimer, sf::Time redTimer) : Entity({0, 0}, x, y, w, h,
                                                                                                                Texture::ID::GreenLight,
                                                                                                                {},
                                                                                                                false),
                                                                                                         nextTime(redTimer),
                                                                                                         currentTime(greenTimer) {}
