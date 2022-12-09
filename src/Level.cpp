#include <numeric>
#include "Level.h"

void incProb(vector<float>& prob, int index, float amount) {
    if (amount >= 1) {
        throw "amount must be less than 1";
    }
    prob[index] += amount;
    for (int i = 0; i < prob.size(); i++) {
        if (i != index) {
            prob[i] -= amount / (prob.size() - 1);
        }
    }
    float testSumProb = std::accumulate(prob.begin(), prob.end(), 0.0f);
    if (abs(testSumProb - 1.0f) > 0.0001f) {
        throw std::runtime_error("Lane spawn probabilities do not sum to 1");
        assert(0);
    }
}

Level::DifficultyMetrics::DifficultyMetrics() {
        level = 1;
        minSpeed = BASE_MIN_SPEED;
        maxSpeed = BASE_MAX_SPEED;
        minSpawnRate = BASE_MIN_SPAWN_RATE;
        maxSpawnRate = BASE_MAX_SPAWN_RATE;
        laneSpawnProb = { 0.8, 0.1, 0.0, 0.0, 0.1 };
        float testSumProb = std::accumulate(laneSpawnProb.begin(), laneSpawnProb.end(), 0.0f);
        if (abs(testSumProb - 1.0f) > 0.0001f) {
            throw std::runtime_error("Lane spawn probabilities do not sum to 1");
        }
    }
Level::DifficultyMetrics::DifficultyMetrics(int level) : DifficultyMetrics() {
    for (int i = 0; i < level; i++) {
        increaseLevel();
    }
}

void Level::DifficultyMetrics::increaseLevel() {
    level++;
    minSpeed += BASE_SPEED_INCREASE;
    maxSpeed += BASE_SPEED_INCREASE;
    minSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    maxSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    int toInc = level / 5 < laneSpawnProb.size() ? level / 5 : laneSpawnProb.size() - 1;
};

Level::Level(int level, sf::Vector2f sceneSize) : sceneBuilder(sceneSize) {
    DifficultyMetrics difficultyMetrics(level);
    auto scene = sceneBuilder
        .addBackground(Texture::ID::Null)
        .addRoad(2, 64*5)
        .build();

    attachChild(std::move(scene));
}
