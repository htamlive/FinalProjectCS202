#pragma once

#include "Lane.h"
#include <functional>

class LaneController : public SceneNode {
public:
    LaneController();

    LaneController(Lane::Type type, unsigned int laneCount, float y,
                   Random<std::normal_distribution<double>> speedDistribution,
                   const std::function<Random<std::normal_distribution<double>>(double speed)> &frequencyFunction);

    LaneController(Lane::Type type, unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                   Random<std::normal_distribution<double>> speed,
                   const std::function<Random<std::normal_distribution<double>>(double speed)> &frequencyFunction);

    void onLightChanged();

    void setLaneHeight(float);

    void setCommuterSize(sf::Vector2f);

private:
    std::vector<Lane *> lanes;

    void generateLanes(Lane::Type type, unsigned int laneCount, float laneHeight, sf::Vector2f commuterSize,
                       Random<std::normal_distribution<double>> speed,
                       const std::function<Random<std::normal_distribution<double>>(double speed)> &frequencyFunction);
};
