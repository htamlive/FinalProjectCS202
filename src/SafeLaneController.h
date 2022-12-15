#pragma once

#include "Lane.h"
#include "SafeLane.h"

class SafeLaneController : public Lane {
public:
    SafeLaneController();

    SafeLaneController(unsigned int laneCount, float y);

    SafeLaneController(unsigned int laneCount, float y, float laneHeight);

    void setLaneHeight(float) override;

    void setPosY(float) override;

private:
    std::vector<SafeLane *> lanes;

    void generateLanes(unsigned int laneCount, float laneHeight);
};