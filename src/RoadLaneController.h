#pragma once

#include "RoadLane.h"
#include <functional>

class RoadLaneController : public Lane {
public:
    RoadLaneController();

    RoadLaneController(unsigned int laneCount, float y,
                       Random<std::normal_distribution<double>> speedDistribution);

    RoadLaneController(unsigned int laneCount, float y, float laneHeight, sf::Vector2f commuterSize,
                       Random<std::normal_distribution<double>> speedDistribution);

    virtual RoadLane::Type getType() const = 0;

    virtual void build();

    void setLaneHeight(float) override;

    void setPosY(float) override;

    void setCommuterSize(sf::Vector2f);

    std::string getClassName() const override;

    void saveCurrentNode(std::ostream& out = std::cout) const override;

    void loadCurrentNode(std::istream& in = std::cin) override;

    void setLaneCount(unsigned int);

    void setSpeedDistribution(Random<std::normal_distribution<double>>);

    void onLoadingFinished() override;

protected:
    std::vector<RoadLane *> lanes;
    unsigned int laneCount = 1;
    float laneHeight = DEF_LANE_HEIGHT;
    sf::Vector2f commuterSize = DEF_COMMUTER_SIZE;
    Random<std::normal_distribution<double>> speedDistribution;
    std::function<Random<std::normal_distribution<double>>(double speed)> frequencyFunction = DEF_FREQUENCY_FUNCTION;

    virtual std::unique_ptr<RoadLane>
    newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const = 0;

private:
    bool shouldSave() const override;

    virtual Texture::ID monoLane() const = 0;

    virtual Texture::ID topLane() const = 0;

    virtual Texture::ID botLane() const = 0;

    virtual Texture::ID midLane() const = 0;
};
