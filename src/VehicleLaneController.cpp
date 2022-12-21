#include <iostream>

#include "VehicleLaneController.h"
#include "Random.h"

VehicleLaneController::VehicleLaneController(unsigned int laneCount, float y, Random<std::normal_distribution<double>> speedDistribution,
                                             const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction,
                                             sf::Time greenTimer, sf::Time redTimer) : RoadLaneController(laneCount, y,
                                                                                        speedDistribution, frequencyFunction),
                                                                     greenTimer(greenTimer), redTimer(redTimer) {}

VehicleLaneController::VehicleLaneController(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                                             Random<std::normal_distribution<double>> speedDistribution,
                                             const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction,
                                             sf::Time greenTimer, sf::Time redTimer) : RoadLaneController(laneCount, y,
                                                                                        laneHeight, commuterSize,
                                                                                        speedDistribution,
                                                                                        frequencyFunction),
                                                                     greenTimer(greenTimer), redTimer(redTimer) {}

RoadLane::Type VehicleLaneController::getType() const {
    return RoadLane::Type::Vehicle;
}

std::unique_ptr<RoadLane>
VehicleLaneController::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    auto lane = std::make_unique<VehicleLane>();
    lane->setCommuterSize(commuterSize);
    lane->setDirection(direction);
    lane->setLaneHeight(laneHeight);
    lane->setPosY(y);
    lane->setFrequency(frequencyFunction(speed));
    lane->setSpeed(speed);
    lane->setLaneTexture(laneTexture);

    auto rand = Random(std::uniform_int_distribution<>(0, std::numeric_limits<int>::max()));
    auto &textures = vehicleTextures.at(lane->getDirection());
    lane->setCommuterTexture(textures[rand.get<int>() % textures.size()]);

    return lane;
}

Texture::ID VehicleLaneController::monoLane() const {
    return Texture::ID::MonoRoadLane;
}

Texture::ID VehicleLaneController::topLane() const {
    return Texture::ID::TopRoadLane;
}

Texture::ID VehicleLaneController::botLane() const {
    return Texture::ID::BotRoadLane;
}

Texture::ID VehicleLaneController::midLane() const {
    return Texture::ID::MidRoadLane;
}

void VehicleLaneController::build() {
    RoadLaneController::build();

    auto trafficLight = std::make_unique<Light>(sf::Vector2f(0, laneHeight * (float) laneCount - DEF_LIGHT_HEIGHT),
                                                sf::Vector2f(DEF_LIGHT_HEIGHT, DEF_LIGHT_HEIGHT), greenTimer, redTimer);
    light = trafficLight.get();
    attachChild(std::move(trafficLight));

    auto rand = Random(std::uniform_int_distribution<>(0, std::numeric_limits<int>::max()));
    for (auto &lane: lanes) {
        auto &textures = vehicleTextures.at(lane->getDirection());
        lane->setCommuterTexture(textures[rand.get<int>() % textures.size()]);
        light->addObserver(dynamic_cast<VehicleLane *>(lane));
    }
}

std::string VehicleLaneController::getClassName() const {
    return "VehicleLaneController";
}

void VehicleLaneController::saveCurrentNode(std::ostream &out) const {
    RoadLaneController::saveCurrentNode(out);
    out << greenTimer.asMilliseconds() << " " << redTimer.asMilliseconds() << std::endl;
}

void VehicleLaneController::loadCurrentNode(std::istream &in) {
    RoadLaneController::loadCurrentNode(in);
    int green, red;
    in >> green >> red;
    greenTimer = sf::milliseconds(green);
    redTimer = sf::milliseconds(red);

    //TODO: link light (child)
}
