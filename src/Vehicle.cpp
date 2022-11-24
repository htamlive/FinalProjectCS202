#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::onLightChanged() {
    std::swap(tmp_velocity, getVelocity());
}

Vehicle::Vehicle() : tmp_velocity(0, 0) {}

Vehicle::Vehicle(sf::Vector2f velocity, float x, float y, float w, float h) : tmp_velocity(0, 0),
                                                                              Entity(velocity, x, y, w, h,
                                                                                     Texture::ID::Vehicle) {}
