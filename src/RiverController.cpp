#include "RiverController.h"

Texture::ID RiverController::monoLane() const {
    return Texture::ID::Wood;
}

Texture::ID RiverController::topLane() const {
    return Texture::ID::Wood;
}

Texture::ID RiverController::botLane() const {
    return Texture::ID::Wood;
}

Texture::ID RiverController::midLane() const {
    return Texture::ID::Wood;
}

std::unique_ptr<RoadLane>
RiverController::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    auto lane = std::make_unique<WoodLane>(Texture::WaterBeforeWood, Texture::Water, Texture::WaterAfterWood, Texture::Wood, y, speed, frequencyFunction(speed));
    lane->setCommuterSize(commuterSize);
    lane->setDirection(direction);
    lane->setLaneHeight(laneHeight);
    lane->setMaxWaterWidth(commuterSize.x * 5);
    lane->spawnWaterInMiddle();

    return lane;
}

RoadLane::Type RiverController::getType() const {
    return RoadLane::Type::River;
}