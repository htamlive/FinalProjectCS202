#include "RiverController.h"

Texture::ID RiverController::monoLane() const {
    return Texture::ID::Water;
}

Texture::ID RiverController::topLane() const {
    return Texture::ID::Water;
}

Texture::ID RiverController::botLane() const {
    return Texture::ID::Water;
}

Texture::ID RiverController::midLane() const {
    return Texture::ID::Water;
}

std::unique_ptr<RoadLane>
RiverController::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    // TODO: wood piece random in length
    auto lane = std::make_unique<River>();
    lane->setCommuterSize(commuterSize);
    lane->setDirection(direction);
    lane->setLaneHeight(laneHeight);
    lane->setPosY(y);
    lane->setFrequency(frequencyFunction(speed));
    lane->setSpeed(speed);
    lane->setLaneTexture(laneTexture);
    lane->setCommuterTexture(Texture::ID::Wood);

    return lane;
}

RoadLane::Type RiverController::getType() const {
    return RoadLane::Type::River;
}

std::string RiverController::getClassName() const {
    return "RiverController";
}

