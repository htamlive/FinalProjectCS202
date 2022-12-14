#include "SafeLaneController.h"
#include "Consts.h"

SafeLaneController::SafeLaneController() = default;

SafeLaneController::SafeLaneController(unsigned int laneCount, float y) {
    setPosition(0, y);
    generateLanes(laneCount, DEF_LANE_HEIGHT);
}

SafeLaneController::SafeLaneController(unsigned int laneCount, float y, float laneHeight) {
    setPosition(0, y);
    generateLanes(laneCount, laneHeight);
}

void SafeLaneController::generateLanes(unsigned int laneCount, float laneHeight) {
    for (auto i = 0; i < laneCount; i++) {
        auto lane = std::make_unique<SafeLane>(laneHeight * (float) i, Texture::ID::SafeLane);
        lane->setLaneHeight(laneHeight);

        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void SafeLaneController::setLaneHeight(float newHeight) {
    for (auto lane: lanes)
        lane->setLaneHeight(newHeight);
}

void SafeLaneController::setPosY(float y) {
    setPosition(0, y);
}