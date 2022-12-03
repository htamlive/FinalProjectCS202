#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}

Vehicle::Vehicle() : tmpVelocity(0, 0) {}

Vehicle::Vehicle(sf::Vector2f velocity, float x, float y, float w, float h, Texture::ID texture) : Entity(velocity, x,
                                                                                                          y, w, h,
                                                                                                          texture),
                                                                                                   tmpVelocity(0, 0) {}
