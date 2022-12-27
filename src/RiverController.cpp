#include "RiverController.h"

Texture::ID RiverController::monoLane() const {
    return Texture::ID::MonoWoodLane;
}

Texture::ID RiverController::topLane() const {
    return Texture::ID::TopWoodLane;
}

Texture::ID RiverController::botLane() const {
    return Texture::ID::BotWoodLane;
}

Texture::ID RiverController::midLane() const {
    return Texture::ID::MidWoodLane;
}

std::unique_ptr<RoadLane>
RiverController::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    direction = riverDirection;
    Texture::ID waterBef, water, waterAft;
    if (laneTexture == monoLane()) {
        waterBef = Texture::ID::WaterBeforeWoodMonoLane;
        water = Texture::ID::WaterMonoLane;
        waterAft = Texture::ID::WaterAfterWoodMonoLane;
    } else if (laneTexture == topLane()) {
        waterBef = Texture::ID::WaterBeforeWoodTopLane;
        water = Texture::ID::WaterTopLane;
        waterAft = Texture::ID::WaterAfterWoodTopLane;
    } else if (laneTexture == botLane()) {
        waterBef = Texture::ID::WaterBeforeWoodBotLane;
        water = Texture::ID::WaterBotLane;
        waterAft = Texture::ID::WaterAfterWoodBotLane;
    } else {
        waterBef = Texture::ID::WaterBeforeWoodMidLane;
        water = Texture::ID::WaterMidLane;
        waterAft = Texture::ID::WaterAfterWoodMidLane;
    }

    auto lane = std::make_unique<WoodLane>(waterBef, water, waterAft,
                                           laneTexture, y, speed, frequencyFunction(speed));
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

std::string RiverController::getClassName() const {
    return "RiverController";
}
