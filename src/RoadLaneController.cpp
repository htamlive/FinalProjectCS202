#include "RoadLaneController.h"
#include "Random.h"

RoadLaneController::RoadLaneController() = default;

RoadLaneController::RoadLaneController(unsigned int laneCount, float y,
                                       Random<std::normal_distribution<double>> speedDistribution) : laneCount(laneCount),
                                                                                                     speedDistribution(speedDistribution) {
    setPosition(0, y);
}

RoadLaneController::RoadLaneController(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                                       Random<std::normal_distribution<double>> speedDistribution) : laneCount(laneCount),
                                                                                                     laneHeight(laneHeight),
                                                                                                     commuterSize(commuterSize),
                                                                                                     speedDistribution(speedDistribution) {
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

std::string RoadLaneController::getClassName() const {
    return "RoadLaneController";
}

void RoadLaneController::saveCurrentNode(std::ostream &out) const {
    Lane::saveCurrentNode(out);
    out << laneCount << " " << laneHeight/SYSTEM_SCALE << " " << commuterSize.x/SYSTEM_SCALE << " " << commuterSize.y/SYSTEM_SCALE << " ";
    out << speedDistribution.dis().mean() << " " << speedDistribution.dis().stddev() << " ";
}

void RoadLaneController::loadCurrentNode(std::istream &in) {
    Lane::loadCurrentNode(in);
    in >> laneCount >> laneHeight >> commuterSize.x >> commuterSize.y;
    laneHeight *= SYSTEM_SCALE;
    commuterSize *= SYSTEM_SCALE;
    double mean, stddev;
    in >> mean >> stddev;
    speedDistribution = std::normal_distribution<double>(mean, stddev);
}

void RoadLaneController::setLaneCount(unsigned int count) {
    laneCount = count;
}

void RoadLaneController::setSpeedDistribution(Random<std::normal_distribution<double>> distribution) {
    speedDistribution = distribution;
}

void RoadLaneController::onLoadingFinished() {
    build();
}

bool RoadLaneController::shouldSave() const {
    return true;
}
