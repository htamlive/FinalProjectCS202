#include "LaneController.h"
#include "Random.h"

// 0 is left, 1 is right
static std::vector<Texture::ID> vehicleTextures[2] = {{Texture::ID::LeftVehicle},
                                                      {Texture::ID::RightVehicle}};
static std::vector<Texture::ID> animalTextures[2] = {{Texture::ID::LeftAnimal},
                                                     {Texture::ID::RightAnimal}};

LaneController::LaneController() = default;

LaneController::LaneController(Lane::Type type, unsigned int laneCount, float y,
                               Random<std::normal_distribution<double>> speedDistribution,
                               const std::function<Random<std::normal_distribution<double>>(
                                       double)> &frequencyFunction) {
    setPosition(0, y);
    generateLanes(type, laneCount, DEF_LANE_HEIGHT, DEF_COMMUTER_SIZE, speedDistribution, frequencyFunction);
}

LaneController::LaneController(
        Lane::Type type, unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
        Random<std::normal_distribution<double>> speedDistribution,
        const std::function<Random<std::normal_distribution<double>>(double speed)> &
        frequencyFunction) {
    setPosition(0, y);
    generateLanes(type, laneCount, laneHeight, commuterSize, speedDistribution,
                  frequencyFunction);
}

void
LaneController::generateLanes(Lane::Type type, unsigned int laneCount, float laneHeight, sf::Vector2f commuterSize,
                              Random<std::normal_distribution<double>> speedDistribution,
                              const std::function<Random<std::normal_distribution<double>>(double)> &frequencyFunction) {
    auto rand = Random(std::uniform_int_distribution<>(
            std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max()));

    for (auto i = 0; i < laneCount; i++) {
        Texture::ID laneTexture = laneCount == 1 ? Texture::ID::MonoVehicleLane
                                  : i == 0 ? Texture::ID::TopVehicleLane
                                  : i == laneCount - 1 ? Texture::ID::BotVehicleLane
                                  : Texture::ID::MidVehicleLane;
        auto direction = rand.get<unsigned int>() % 2;
        Texture::ID commuterTexture;
        if (type == Lane::Type::Vehicle)
            commuterTexture = vehicleTextures[direction][rand.get<unsigned int>() % vehicleTextures[direction].size()];
        else
            commuterTexture = animalTextures[direction][rand.get<unsigned int>() % animalTextures[direction].size()];
        auto speed = speedDistribution.get<double>();

        auto lane = std::make_unique<Lane>(
                type, commuterTexture, laneTexture, laneHeight * (float)i, speed, frequencyFunction(speed));
        lane->setCommuterSize(commuterSize);
        lane->setDirection((Lane::Direction) direction);
        lane->setLaneHeight(laneHeight);

        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void LaneController::onLightChanged() {
    for (auto &lane: lanes) {
        lane->onLightChanged();
    }
}

void LaneController::setLaneHeight(float height) {
    for (auto &lane: lanes) {
        lane->setLaneHeight(height);
    }
}

void LaneController::setCommuterSize(sf::Vector2f size) {
    for (auto &lane: lanes) {
        lane->setCommuterSize(size);
    }
}