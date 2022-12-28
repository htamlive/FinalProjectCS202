#include "Level.h"

#include <vector>
#include <memory>

struct DifficultyMetrics {
    int level;
    float minSpeed;
    float maxSpeed;
    float minSpawnRate;
    float maxSpawnRate;
    std::vector<float> laneSpawnProb;
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

class LevelGenerator {
public:
    std::unique_ptr<Level> makeLevel(int level, sf::Vector2f sceneSize);
};
