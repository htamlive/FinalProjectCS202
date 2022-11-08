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

TrafficLight::TrafficLight(float x, float y, float w, float h) : Entity({0, 0}, x, y, w, h,
                                                                        Texture::ID::TrafficLightSprites) {}
