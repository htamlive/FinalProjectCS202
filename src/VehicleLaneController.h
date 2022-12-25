#pragma once

#include "RoadLaneController.h"
#include "Light.h"

class VehicleLaneController : public RoadLaneController {
private:
    const std::map<RoadLane::Direction, std::vector<Texture::ID>> vehicleTextures = {{RoadLane::Direction::Left,  {Texture::ID::LeftVehicle}},
                                                                                     {RoadLane::Direction::Right, {Texture::ID::RightVehicle}}};
    Light *light = nullptr;
    sf::Time greenDuration = {}, redDuration = {};

    Texture::ID monoLane() const override;

    Texture::ID topLane() const override;

    Texture::ID botLane() const override;

    Texture::ID midLane() const override;

protected:
    std::unique_ptr<RoadLane>
    newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const override;

public:
    using RoadLaneController::RoadLaneController;

    VehicleLaneController(unsigned int laneCount, float y,
                          Random<std::normal_distribution<double>> speedDistribution,
                          const std::function<Random<std::normal_distribution<double>>(
                                  double speed)> &frequencyFunction,
                          sf::Time greenDuration, sf::Time redDuration);

    VehicleLaneController(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                          Random<std::normal_distribution<double>> speedDistribution,
                          const std::function<Random<std::normal_distribution<double>>(
                                  double speed)> &frequencyFunction,
                          sf::Time greenDuration, sf::Time redDuration);

    RoadLane::Type getType() const override;

    void setRedDuration(sf::Time);

    void setGreenDuration(sf::Time);

    void build() override;
};