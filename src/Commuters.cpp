#include "Commuters.h"
#include "Consts.h"
#include "TextureHolder.h"

Category::Type Animal::getCategory() const {
    return Category::Enemy;
}

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}

Category::Type Vehicle::getCategory() const {
    return Category::Enemy;
}

Category::Type Wood::getCategory() const {
    return Category::Wood;
}