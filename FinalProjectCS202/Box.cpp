#include <cmath>

#include "Box.h"

Box::Box(float x, float y, float w, float h) {
    setPosition(x, y);
    setSize({w, h});
}

bool Box::isCollided(const Box &other) const {
    auto this_tl = getPosition();
    auto this_rd = getPosition() + getSize();
    auto other_tl = other.getPosition();
    auto other_rd = other.getPosition() + other.getSize();

    return this_tl.x <= other_rd.x && this_rd.x >= other_tl.x && this_tl.y <= other_rd.y && this_rd.y >= other_tl.y;
}

float Box::getDis(const Box &other) const {
    auto this_c = getPosition() + (getPosition() + getSize());
    this_c.x /= 2; this_c.y /= 2;
    auto other_c = other.getPosition() + (other.getPosition() + other.getSize());
    other_c.x /= 2; other_c.y /= 2;

    return std::sqrt((this_c.x - other_c.x) * (this_c.x - other_c.x) + (this_c.y - other_c.y) * (this_c.y - other_c.y));
}
