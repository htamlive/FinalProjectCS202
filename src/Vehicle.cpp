#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmp_velocity);
    tmp_velocity = oldVelocity;
}
