#pragma once

#include "RoadLaneController.h"

class RiverController : public RoadLaneController {
private:
    Texture::ID monoLane() const override;

    Texture::ID topLane() const override;

    Texture::ID botLane() const override;

    Texture::ID midLane() const override;

protected:
    std::unique_ptr<RoadLane>
    newLane(Texture::ID laneTexture, RoadLane::Direction direction, float speed, float y) const override;

public:
    using RoadLaneController::RoadLaneController;

    RoadLane::Type getType() const override;

    std::string getClassName() const override;
};