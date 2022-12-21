#include "Commuters.h"
#include "Consts.h"
#include "TextureHolder.h"

Category::Type Animal::getCategory() const {
    return Category::Enemy;
}

std::string Animal::getClassName() const {
    return "Animal";
}

void Vehicle::onLightChanged() {
    auto oldVelocity = getVelocity();
    setVelocity(tmpVelocity);
    tmpVelocity = oldVelocity;
}

Category::Type Vehicle::getCategory() const {
    if (getVelocity() == sf::Vector2f(0, 0)) {
        return Category::Obstacle;
    }
    else
        return Category::Enemy;
}

std::string Vehicle::getClassName() const {
    return "Vehicle";
}

Category::Type Wood::getCategory() const {
    return Category::Wood;
}

std::string Wood::getClassName() const {
    return "Wood";
}
