#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const {
    // Downcast Vehicle back to sf::Transformable then upcast to sf::Sprite to preserve properties i.e., position, scale, origin, rotation.
    sf::Transformable trans = *this;
    auto sprite = dynamic_cast<sf::Sprite &>(trans);

    animation.toSprite(sprite);
    target.draw(sprite, state);
}

void Vehicle::onLightChanged() {
    std::swap(tmp_velocity, getVelocity());
}

Vehicle::Vehicle() : tmp_velocity(0, 0) {}

Vehicle::Vehicle(sf::Vector2f velocity, float x, float y, float w, float h) : tmp_velocity(0, 0),
                                                                              Entity(velocity, x, y, w, h,
                                                                                     Texture::ID::VehicleSprites) {}
