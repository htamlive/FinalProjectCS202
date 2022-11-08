#include "TrafficLight.h"
#include "TextureHolder.h"
#include "Consts.h"

void TrafficLight::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    animation.toSprite(sprite);
    target.draw(sprite, state);
}

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
                                                                                                                Texture::ID::GreenLightSprite,
                                                                                                                {},
                                                                                                                false),
                                                                                                         nextTime(redTimer),
                                                                                                         currentTime(greenTimer) {}
