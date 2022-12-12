#include "RoadLanes.h"
#include "Random.h"

// 0 is left, 1 is right
static std::vector<Texture::ID> vehicleTextures[2] = {{Texture::ID::LeftVehicle},
                                                      {Texture::ID::RightVehicle}};
static std::vector<Texture::ID> animalTextures[2] = {{Texture::ID::LeftAnimal},
                                                     {Texture::ID::RightAnimal}};

RoadLanes::RoadLanes() = default;

RoadLanes::RoadLanes(unsigned int laneCount, float y,
                     Random<std::normal_distribution<double>> speedDistribution,
                     const std::function<Random<std::normal_distribution<double>>(
                             double)> &frequencyFunction) : laneCount(laneCount),
                                                            speedDistribution(speedDistribution),
                                                            frequencyFunction(frequencyFunction) {
    setPosition(0, y);
}

RoadLanes::RoadLanes(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                     Random<std::normal_distribution<double>> speedDistribution,
                     const std::function<Random<std::normal_distribution<double>>(double speed)> &
                     frequencyFunction) : laneCount(laneCount), laneHeight(laneHeight), commuterSize(commuterSize),
                                          speedDistribution(speedDistribution), frequencyFunction(frequencyFunction) {
    setPosition(0, y);
}

void RoadLanes::build() {
    auto rand = Random(std::uniform_int_distribution<>(0, std::numeric_limits<int>::max()));

    for (auto i = 0; i < laneCount; i++) {
        Texture::ID laneTexture =
                laneCount == 1 ? monoLane() : i == 0 ? topLane() : i == laneCount - 1 ? botLane() : midLane();
        auto direction = (RoadLane::Direction) (rand.get<int>() % 2);
        auto speed = speedDistribution.get<float>();

        auto lane = newLane(laneTexture, direction, speed, laneHeight * (float) i);
        lanes.push_back(lane.get());
        attachChild(std::move(lane));
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

void RoadLanes::setCommuterSize(sf::Vector2f size) {
    for (auto &lane: lanes) {
        lane->setCommuterSize(size);
    }
}