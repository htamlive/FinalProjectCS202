#pragma once

#include "Lane.h"
#include "SafeLane.h"

class SafeLanes : public Lane {
public:
    SafeLanes();

    SafeLanes(unsigned int laneCount, float y);

    SafeLanes(unsigned int laneCount, float y, float laneHeight);

    void setLaneHeight(float) override;

    void setPosY(float) override;

    float getTopY() const override;

    float getBottomY() const override;

private:
    std::vector<SafeLane *> lanes;

    void generateLanes(unsigned int laneCount, float laneHeight);
};