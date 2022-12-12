#include <iostream>

#include "VehicleLanes.h"
#include "Random.h"

VehicleLanes::VehicleLanes(unsigned int laneCount, float y, Random<std::normal_distribution<double>> speedDistribution,
                           const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction,
                           sf::Time greenTimer, sf::Time redTimer) : RoadLanes(laneCount, y,
                                                                               speedDistribution, frequencyFunction),
                                                                     greenTimer(greenTimer), redTimer(redTimer) {}

VehicleLanes::VehicleLanes(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                           Random<std::normal_distribution<double>> speedDistribution,
                           const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction,
                           sf::Time greenTimer, sf::Time redTimer) : RoadLanes(laneCount, y,
                                                                               laneHeight, commuterSize,
                                                                               speedDistribution,
                                                                               frequencyFunction),
                                                                     greenTimer(greenTimer), redTimer(redTimer) {}

RoadLane::Type VehicleLanes::getType() const {
    return RoadLane::Type::Vehicle;
}

std::unique_ptr<RoadLane>
VehicleLanes::newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const {
    std::cout << (int) direction << '\n';
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

Texture::ID VehicleLanes::monoLane() const {
    return Texture::ID::MonoRoadLane;
}

Texture::ID VehicleLanes::topLane() const {
    return Texture::ID::TopRoadLane;
}

Texture::ID VehicleLanes::botLane() const {
    return Texture::ID::BotRoadLane;
}

Texture::ID VehicleLanes::midLane() const {
    return Texture::ID::MidRoadLane;
}

void VehicleLanes::build() {
    RoadLanes::build();

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