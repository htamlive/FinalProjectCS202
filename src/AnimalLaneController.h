#pragma once

#include "RoadLaneController.h"

class AnimalLaneController : public RoadLaneController {
private:
    const std::map<RoadLane::Direction, std::vector<Texture::ID>> animalTextures = {{RoadLane::Direction::Left,  {Texture::ID::LeftCucumber,  Texture::ID::LeftPlane}},
                                                                                    {RoadLane::Direction::Right, {Texture::ID::RightCucumber, Texture::ID::RightPlane}}};

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