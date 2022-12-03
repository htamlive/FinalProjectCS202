#include "LaneController.h"
#include "Random.h"

// 0 is left, 1 is right
static std::vector<Texture::ID> vehicleTextures[2] = {{Texture::ID::LeftVehicle},
                                                      {Texture::ID::RightVehicle}};
static std::vector<Texture::ID> animalTextures[2] = {{Texture::ID::LeftAnimal},
                                                     {Texture::ID::RightAnimal}};

LaneController::LaneController() = default;

// TODO: Are there vehicles/animals of different widths?
LaneController::LaneController(
        Lane::Type type, unsigned int laneCount, float y, float laneHeight,
        float commuterWidth, float commuterHeight,
        Random<std::normal_distribution<double>> speedDistribution,
        const std::function<Random<std::normal_distribution<double>>(double speed)> &
        frequencyFunction) {
    setPosition(0, y);

    auto rand = Random(std::uniform_int_distribution<>(
            std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max()));

    float laneY = 0;
    for (unsigned int i = 0; i < laneCount; i++, laneY += laneHeight) {
        Texture::ID laneTexture = laneCount == 1 ? Texture::ID::MonoVehicleLane
                                  : i == 0 ? Texture::ID::TopVehicleLane
                                  : i == laneCount - 1 ? Texture::ID::BotVehicleLane
                                  : Texture::ID::MidVehicleLane;
        auto direction = rand.get<unsigned int>() % 2;
        Texture::ID commuterTexture;
        if (type == Lane::Type::Vehicle)
            commuterTexture =
                    vehicleTextures[direction][rand.get<unsigned int>() % vehicleTextures[direction].size()];
        else
            commuterTexture =
                    animalTextures[direction][rand.get<unsigned int>() % animalTextures[direction].size()];

        auto speed = speedDistribution.get<double>();
        auto lane = std::make_unique<Lane>(
                type, commuterTexture, laneTexture, laneY, laneHeight, commuterWidth,
                commuterHeight, (Lane::Direction) direction, speed,
                frequencyFunction(speed));
        lanes.push_back(lane.get());
        attachChild(std::move(lane));
    }
}

void LaneController::onLightChanged() {
    for (auto &lane: lanes) {
        lane->onLightChanged();
    }
}