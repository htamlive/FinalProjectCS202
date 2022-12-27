#include "AnimalLaneController.h"

Texture::ID AnimalLaneController::monoLane() const {
    return Texture::ID::MonoRoadLane;
}

Texture::ID AnimalLaneController::topLane() const {
    return Texture::ID::TopRoadLane;
}

Texture::ID AnimalLaneController::botLane() const {
    return Texture::ID::BotRoadLane;
}

Texture::ID AnimalLaneController::midLane() const {
    return Texture::ID::MidRoadLane;
}

std::unique_ptr<RoadLane>
AnimalLaneController::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    auto lane = std::make_unique<AnimalLane>();
    lane->setCommuterSize(commuterSize);
    lane->setDirection(direction);
    lane->setLaneHeight(laneHeight);
    lane->setPosY(y);
    lane->setFrequency(frequencyFunction(speed));
    lane->setSpeed(speed);
    lane->setLaneTexture(laneTexture);

    auto rand = Random(std::uniform_int_distribution<>(0, std::numeric_limits<int>::max()));
    auto &textures = animalTextures.at(lane->getDirection());
    lane->setCommuterTexture(textures[rand.get<int>() % textures.size()]);

    return lane;
}

RoadLane::Type AnimalLaneController::getType() const {
    return RoadLane::Type::Animal;
}

std::string AnimalLaneController::getClassName() const {
    return "AnimalLaneController";
}
