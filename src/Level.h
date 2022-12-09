#pragma once
#include <SFML/System/Vector2.hpp>
#include <assert.h>
#include "SceneBuilder.h"
#include "SceneNode.h"

const float BASE_MIN_SPAWN_RATE = 0.5f;
const float BASE_MAX_SPAWN_RATE = 1.5f;
const float BASE_SPAWN_RATE_DECREASE = 0.01;

const float BASE_MIN_SPEED = 0.5f;
const float BASE_MAX_SPEED = 1.5f;
const float BASE_SPEED_INCREASE = 0.01;

class Level : public SceneNode {

    class DifficultyMetrics {
        int level;
        float minSpeed;
        float maxSpeed;
        float minSpawnRate;
        float maxSpawnRate;
        vector<float> laneSpawnProb;
    public:
        DifficultyMetrics();
        DifficultyMetrics(int level);
        void increaseLevel();
        int getLevel() const { return level; }
        float getMinSpeed() const { return minSpeed; }
        float getMaxSpeed() const { return maxSpeed; }
        float getMinSpawnRate() const { return minSpawnRate; }
        float getMaxSpawnRate() const { return maxSpawnRate; }
    };

    SceneBuilder sceneBuilder;

public:
    Level(int level, sf::Vector2f sceneSize) : sceneBuilder(sceneSize) {
        DifficultyMetrics difficultyMetrics(level);
        auto scene = sceneBuilder
            .addBackground(Texture::ID::Null)
            .build();

        attachChild(std::move(scene));
    }
};
