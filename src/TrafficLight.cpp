#include "TrafficLight.h"
#include "TextureHolder.h"
#include "Consts.h"

void TrafficLight::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    sprite.setTexture(TextureHolder::instance().get(spriteStage), true);
    target.draw(sprite, state);
}

void TrafficLight::updateCurrent(sf::Time dt) {
    Entity::updateCurrent(dt);
}

TrafficLight::TrafficLight() {}

TrafficLight::TrafficLight(float x, float y, float w, float h) : Entity(Texture::ID::TrafficLightSprites,
                                                                        {0, 0}, x, y, w, h) {}
