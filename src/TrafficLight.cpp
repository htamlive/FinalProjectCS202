#include "TrafficLight.h"
#include "TextureHolder.h"
#include "Consts.h"

void TrafficLight::updateCurrent(sf::Time dt) {
    timer += dt;
    if (timer >= currentTime)
        changeLight();
    else if (timer >= currentTime - LIGHT_CHANGING_DURATION) {
        changingPhase();
    }

    Entity::updateCurrent(dt);
}

void TrafficLight::changeLight() {
    std::swap(currentTime, nextTime);
    timer = sf::Time::Zero;

    std::swap(sprites.first, sprites.second);
    animation = AnimationMachine(sprites.first.first, {}, false);

    // TODO: Signal light changing to vehicles
}

void TrafficLight::changingPhase() {
    auto duration = std::min(LIGHT_CHANGING_DURATION, currentTime - timer);
    animation = AnimationMachine(sprites.first.second, duration, false);
}

TrafficLight::TrafficLight(sf::Vector2f position, sf::Vector2f size, sf::Time greenTimer, sf::Time redTimer) : Entity(Texture::ID::GreenLight,
                                                                                                                      position, size,
                                                                                                                      {0, 0},
                                                                                                                      {},
                                                                                                                      false),
                                                                                                               nextTime(redTimer),
                                                                                                               currentTime(greenTimer) {}
