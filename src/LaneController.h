#pragma once

#include "Lane.h"
#include <functional>

class LaneController : public SceneNode {
public:
    LaneController();

    LaneController(Lane::Type type, unsigned int laneCount, float y, float laneHeight, float commuterWidth,
                   float commuterHeight, Random<std::normal_distribution<double>> speed,
                   const std::function<Random<std::normal_distribution<double>>(double speed)>& frequencyFunction);

private:
    void onLightChanged();

    std::vector <Lane *> lanes;
};
