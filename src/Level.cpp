#include "Level.h"
#include "Consts.h"
#include <numeric>
#include <random>

void incProb(vector<float> &prob, int index, float amount) {
    prob[index] += amount;
}

Level::DifficultyMetrics::DifficultyMetrics() {
    level = 1;
    minSpeed = BASE_MIN_SPEED;
    maxSpeed = BASE_MAX_SPEED;
    minSpawnRate = BASE_MIN_SPAWN_RATE;
    maxSpawnRate = BASE_MAX_SPAWN_RATE;
    laneSpawnProb = vector<float>(MAX_LANE_COUNT, .0f);
    float testSumProb =
        std::accumulate(laneSpawnProb.begin(), laneSpawnProb.end(), 0.0f);
}
Level::DifficultyMetrics::DifficultyMetrics(int level) : DifficultyMetrics() {
    if (level <= 0) {
        throw std::invalid_argument("Level must be greater than 0");
    }
    for (int i = 0; i < level; i++) {
        increaseLevel();
    }
    std::cout << "Level " << level << " difficulty metrics:" << std::endl;
    std::cout << "minSpeed: " << minSpeed << std::endl;
    std::cout << "maxSpeed: " << maxSpeed << std::endl;
    std::cout << "minSpawnRate: " << minSpawnRate << std::endl;
    std::cout << "maxSpawnRate: " << maxSpawnRate << std::endl;
    std::cout << "laneSpawnProb: ";
    for (int i = 0; i < laneSpawnProb.size(); i++) {
        std::cout << laneSpawnProb[i] << " ";
    }
    std::cout << std::endl;
}

void Level::DifficultyMetrics::increaseLevel() {
    level++;
    minSpeed += BASE_SPEED_INCREASE;
    maxSpeed += BASE_SPEED_INCREASE;
    minSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    maxSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    int toInc = level / 3;
    incProb(laneSpawnProb, toInc, 0.20f);
};

Level::Level(int level, sf::Vector2f sceneSize) : sceneBuilder(sceneSize) {
    DifficultyMetrics difficultyMetrics(level);
    random = std::discrete_distribution<unsigned>(
        difficultyMetrics.laneSpawnProb.begin(),
        difficultyMetrics.laneSpawnProb.end());
    auto builder = SceneBuilder(sceneSize);
    builder.addBackground(Texture::ID::Null);
    float gridHeight = sceneSize.y / GRID_SIZE.y;
    for (int i = 1; i < gridHeight - 2; i++) {
        if (i == gridHeight - 1) {
            continue;
        }
        float laneType = random.get<float>() + 1;
        while (i + laneType >= gridHeight) {
            laneType = random.get<float>() + 1;
        }
        builder.addRoad(laneType, i * GRID_SIZE.y, difficultyMetrics.minSpeed,
                        difficultyMetrics.maxSpeed,
                        difficultyMetrics.minSpawnRate,
                        difficultyMetrics.maxSpawnRate);
        i += laneType;
    }

    auto scene = builder.build();
    attachChild(std::move(scene));
}
//
// int main() {
//     Level level(1, sf::Vector2f(800, 600));
//     Level level1(2, sf::Vector2f(800, 600));
//     Level level2(3, sf::Vector2f(800, 600));
//     Level level3(4, sf::Vector2f(800, 600));
//     Level level4(6, sf::Vector2f(800, 600));
//     Level level5(13, sf::Vector2f(800, 600));
//     Level level6(30, sf::Vector2f(800, 600));
//     return 0;
// }
