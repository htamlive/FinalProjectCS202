#include "Vehicle.h"
#include "TextureHolder.h"
#include "Consts.h"

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}