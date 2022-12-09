#include "SafeLanes.h"
#include "Consts.h"

SafeLanes::SafeLanes() = default;

SafeLanes::SafeLanes(unsigned int laneCount, float y) {
    setPosition(0, y);
    generateLanes(laneCount, DEF_LANE_HEIGHT);
}

SafeLanes::SafeLanes(unsigned int laneCount, float y, float laneHeight) {
    setPosition(0, y);
    generateLanes(laneCount, laneHeight);
}

void SafeLanes::generateLanes(unsigned int laneCount, float laneHeight) {
    for (auto i = 0; i < laneCount; i++) {
        auto lane = std::make_unique<SafeLane>(laneHeight * (float)i, Texture::ID::SafeLane);
        lane->setLaneHeight(laneHeight);

        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void SafeLanes::setLaneHeight(float newHeight) {
    for (auto lane : lanes)
        lane->setLaneHeight(newHeight);
}

void SafeLanes::setPosY(float y) {
    setPosition(0, y);
}

float SafeLanes::getTopY() const {
    return getPosition().y;
}

float SafeLanes::getBottomY() const {
    auto y = getTopY();
    for (auto &lane: lanes) {
        y = std::min(y, lane->getBottomY());
    }
    return y;
}
