#include "Light.h"
#include "TextureHolder.h"
#include "Consts.h"

void Light::updateCurrent(sf::Time dt) {
    timer += dt;
    if (timer >= currentTime)
        changeLight();
    else if (timer >= currentTime - LIGHT_CHANGING_DURATION && animation.getID() != sprites.first.second) {
        changingPhase();
    }

    Entity::updateCurrent(dt);
}

void Light::addObserver(LightObserver *observer) {
    observers.push_back(observer);
}

void Light::changeLight() {
    std::swap(currentTime, nextTime);
    timer = sf::Time::Zero;

    std::swap(sprites.first, sprites.second);
    animation = AnimationMachine(sprites.first.first, {}, false);

    // Signal light changing to vehicles
    for (auto &observer: observers)
        observer->onLightChanged();
}

void Light::changingPhase() {
    auto duration = std::min(LIGHT_CHANGING_DURATION, currentTime - timer);
    animation = AnimationMachine(sprites.first.second, duration, false);
}

Light::Light(sf::Vector2f position, sf::Vector2f size, sf::Time greenTimer, sf::Time redTimer) : Entity(
        Texture::ID::GreenLight,
        position, size,
        {0, 0},
        {},
        false),
                                                                                                 nextTime(redTimer),
                                                                                                 currentTime(
                                                                                                         greenTimer) {}

std::string Light::getClassName() const {
    return "Light";
}