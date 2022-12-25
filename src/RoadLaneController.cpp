#include "RoadLaneController.h"
#include "Random.h"

RoadLaneController::RoadLaneController() = default;

RoadLaneController::RoadLaneController(unsigned int laneCount, float y,
                                       Random<std::normal_distribution<double>> speedDistribution,
                                       const std::function<Random<std::normal_distribution<double>>(
                             double)> &frequencyFunction) : laneCount(laneCount),
                                                            speedDistribution(speedDistribution),
                                                            frequencyFunction(frequencyFunction) {
    setPosition(0, y);
}

RoadLaneController::RoadLaneController(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                                       Random<std::normal_distribution<double>> speedDistribution,
                                       const std::function<Random<std::normal_distribution<double>>(double speed)> &
                     frequencyFunction) : laneCount(laneCount), laneHeight(laneHeight), commuterSize(commuterSize),
                                          speedDistribution(speedDistribution), frequencyFunction(frequencyFunction) {
    setPosition(0, y);
}

void RoadLaneController::build() {
    auto rand = Random(std::uniform_int_distribution<>(0, std::numeric_limits<int>::max()));

    for (auto i = 0; i < laneCount; i++) {
        Texture::ID laneTexture =
                laneCount == 1 ? monoLane() : i == 0 ? topLane() : i == laneCount - 1 ? botLane() : midLane();
        auto direction = (RoadLane::Direction) (rand.get<int>() % 2);
        // get only positive values
        auto speed = speedDistribution.get<float>(0, std::numeric_limits<float>::max());

        auto lane = newLane(laneTexture, direction, speed, laneHeight * (float) i);
        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void RoadLaneController::setLaneHeight(float height) {
    for (auto &lane: lanes) {
        lane->setLaneHeight(height);
    }
}

void RoadLaneController::setPosY(float y) {
    setPosition(0, y);
}

void RoadLaneController::setCommuterSize(sf::Vector2f size) {
    for (auto &lane: lanes) {
        lane->setCommuterSize(size);
    }
}

void RoadLaneController::setLaneCount(unsigned int count) {
    laneCount = count;
}

void RoadLaneController::setSpeedDistribution(Random<std::normal_distribution<double>> distribution) {
    speedDistribution = distribution;
}

void RoadLaneController::setFrequencyFunction(const std::function<Random<std::normal_distribution<double>>(double)> &function) {
    frequencyFunction = function;
}
