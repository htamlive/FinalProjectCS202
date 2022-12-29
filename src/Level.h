#pragma once
#include <SFML/System/Vector2.hpp>
#include <assert.h>
#include <random>
#include "Enums.h"
#include "SceneNode.h"
#include "Random.h"

const float BASE_MIN_SPAWN_RATE = 0.5f;
const float BASE_MAX_SPAWN_RATE = 1.5f;
const float BASE_SPAWN_RATE_DECREASE = 0.01;

const float BASE_MIN_SPEED = 100.f;
const float BASE_MAX_SPEED = 200.f;
const float BASE_SPEED_INCREASE = 25.f;
const int   MAX_LANE_COUNT = 8;

class Level : public SceneNode {
    bool shouldSave() const override;

public:
    void removeObject(const SceneNode &object);
    void loadCurrentNode(std::istream &in = std::cin) override;
    void saveCurrentNode(std::ostream &out = std::cout) const override;
    std::string getClassName() const override;
};
