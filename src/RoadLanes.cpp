#include "RoadLanes.h"
#include "Random.h"

// 0 is left, 1 is right
static std::vector<Texture::ID> vehicleTextures[2] = {{Texture::ID::LeftVehicle},
                                                      {Texture::ID::RightVehicle}};
static std::vector<Texture::ID> animalTextures[2] = {{Texture::ID::LeftAnimal},
                                                     {Texture::ID::RightAnimal}};

RoadLanes::RoadLanes() = default;

RoadLanes::RoadLanes(RoadLane::Type type, unsigned int laneCount, float y,
                     Random<std::normal_distribution<double>> speedDistribution,
                     const std::function<Random<std::normal_distribution<double>>(
                                       double)> &frequencyFunction) {
    setPosition(0, y);
    generateLanes(type, laneCount, DEF_LANE_HEIGHT, DEF_COMMUTER_SIZE, speedDistribution, frequencyFunction);
}

RoadLanes::RoadLanes(
        RoadLane::Type type, unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
        Random<std::normal_distribution<double>> speedDistribution,
        const std::function<Random<std::normal_distribution<double>>(double speed)> &
        frequencyFunction) {
    setPosition(0, y);
    generateLanes(type, laneCount, laneHeight, commuterSize, speedDistribution,
                  frequencyFunction);
}

void
RoadLanes::generateLanes(RoadLane::Type type, unsigned int laneCount, float laneHeight, sf::Vector2f commuterSize,
                         Random<std::normal_distribution<double>> speedDistribution,
                         const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction) {
    auto rand = Random(std::uniform_int_distribution<>(
            std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max()));

    for (auto i = 0; i < laneCount; i++) {
        Texture::ID laneTexture = laneCount == 1 ? Texture::ID::MonoRoadLane
                                  : i == 0 ? Texture::ID::TopRoadLane
                                  : i == laneCount - 1 ? Texture::ID::BotRoadLane
                                  : Texture::ID::MidRoadLane;
        auto direction = rand.get<unsigned int>() % 2;
        Texture::ID commuterTexture;
        if (type == RoadLane::Type::Vehicle)
            commuterTexture = vehicleTextures[direction][rand.get<unsigned int>() % vehicleTextures[direction].size()];
        else
            commuterTexture = animalTextures[direction][rand.get<unsigned int>() % animalTextures[direction].size()];
        auto speed = speedDistribution.get<double>();

        auto lane = std::make_unique<RoadLane>(
                type, commuterTexture, laneTexture, laneHeight * (float)i, speed, frequencyFunction(speed));
        lane->setCommuterSize(commuterSize);
        lane->setDirection((RoadLane::Direction) direction);
        lane->setLaneHeight(laneHeight);

        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void RoadLanes::onLightChanged() {
    for (auto &lane: lanes) {
        lane->onLightChanged();
    }
}

void RoadLanes::setLaneHeight(float height) {
    for (auto &lane: lanes) {
        lane->setLaneHeight(height);
    }
}

void RoadLanes::setPosY(float y) {
    setPosition(0, y);
}

float RoadLanes::getTopY() const {
    return getPosition().y;
}

float RoadLanes::getBottomY() const {
    auto y = getTopY();
    for (auto &lane: lanes) {
        y = std::min(y, lane->getBottomY());
    }
    return y;
}

void RoadLanes::setCommuterSize(sf::Vector2f size) {
    for (auto &lane: lanes) {
        lane->setCommuterSize(size);
    }
}