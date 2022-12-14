#pragma once

#include "RoadLane.h"
#include <functional>

class RoadLanes : public Lane {
  public:
    RoadLanes();

    RoadLanes(RoadLane::Type type, unsigned int laneCount, float y,
              Random<std::normal_distribution<double>> speedDistribution,
              const std::function<Random<std::normal_distribution<double>>(
                  double speed)> &frequencyFunction);

    RoadLanes(RoadLane::Type type, unsigned int laneCount, float y,
              float laneHeight, sf::Vector2f commuterSize,
              Random<std::normal_distribution<double>> speed,
              const std::function<Random<std::normal_distribution<double>>(
                  double speed)> &frequencyFunction);

    void setLaneHeight(float) override;

    void setPosY(float) override;

    float getTopY() const override;

    float getBottomY() const override;

    void onLightChanged();

    void setCommuterSize(sf::Vector2f);

  private:
    std::vector<RoadLane *> lanes;

    void
    generateLanes(RoadLane::Type type, unsigned int laneCount, float laneHeight,
                  sf::Vector2f commuterSize,
                  Random<std::normal_distribution<double>> speed,
                  const std::function<Random<std::normal_distribution<double>>(
                      double speed)> &frequencyFunction);
};
