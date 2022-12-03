#include "LaneController.h"
#include "Random.h"

static std::vector<Texture::ID> vehicleTextures = {Texture::ID::Vehicle};
static std::vector<Texture::ID> animalTextures = {Texture::ID::Animal};

LaneController::LaneController() = default;

// TODO: Are there vehicles/animals of different widths?
LaneController::LaneController(
    Lane::Type type, unsigned int laneCount, float y, float laneHeight,
    float commuterWidth, float commuterHeight,
    Random<std::normal_distribution<double>> speedDistribution,
    std::function<Random<std::normal_distribution<double>>(double speed)>
        frequencyFunction) {
    setPosition(0, y);

    auto rand = Random(std::uniform_int_distribution<>(
        std::numeric_limits<int>::lowest(), std::numeric_limits<int>::max()));

    for (unsigned int i = 0; i < laneCount; i++, y += laneHeight) {
        Texture::ID laneTexture = i == 0               ? Texture::ID::TopLane
                                  : i == laneCount - 1 ? Texture::ID::BotLane
                                                       : Texture::ID::MidLane;
        Texture::ID commuterTexture;
        if (type == Lane::Type::Vehicle)
            commuterTexture =
                vehicleTextures[0];
        else
            commuterTexture =
                animalTextures[0];

        auto speed = speedDistribution.get<double>();
        auto lane = std::make_unique<Lane>(
            type, commuterTexture, laneTexture, y, laneHeight, commuterWidth,
            commuterHeight, (Lane::Direction)(rand.get<int>() % 2), speed,
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