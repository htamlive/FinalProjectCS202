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
    float mapWidth = sceneSize.x / GRID_SIZE.x;
    float mapHeight = sceneSize.y / GRID_SIZE.y;
    DifficultyMetrics difficultyMetrics(level);
    random = std::discrete_distribution<unsigned>(
            difficultyMetrics.laneSpawnProb.begin(),
            difficultyMetrics.laneSpawnProb.end());
    auto builder = SceneBuilder(sceneSize);
    builder.addBackground(Texture::ID::Background);

    for (int i = 1; i < mapHeight - 2; i++) {
        float laneType;
        do {
            laneType = random.get<float>() + 1;
        } while (i + laneType >= mapHeight);

        auto prob = Random(std::uniform_real_distribution(0.f, 1.f)).get<float>();
        auto type = prob <= VEHICLE_LANE_PROB ? RoadLane::Type::Vehicle : prob <= VEHICLE_LANE_PROB + ANIMAL_LANE_PROB
                                                                          ? RoadLane::Type::Animal
                                                                          : RoadLane::Type::River;
        builder.addRoadController(type, laneType, i * GRID_SIZE.y, difficultyMetrics.minSpeed,
                                  difficultyMetrics.maxSpeed,
                                  difficultyMetrics.minSpawnRate,
                                  difficultyMetrics.maxSpawnRate);
        auto shouldPlaceObstacle = Random(std::bernoulli_distribution(0.2));
        auto shouldPlaceReward = Random(std::bernoulli_distribution(0.05));
        for (int j = 0; j < laneType; j++) {
            for (int k = 0; k < mapWidth; k++) {
                if (shouldPlaceReward.get<bool>()) {
                    builder.addReward({k * GRID_SIZE.x,
                                       (i + j) * GRID_SIZE.y}, GRID_SIZE);
                }
            }
        }
        i += laneType;
        if (i >= mapHeight - 2) {
            break;
        }
        for (int j = 0; j < mapWidth; j++) {
            if (shouldPlaceObstacle.get<bool>())
                builder.addRock(
                        sf::Vector2f(j * GRID_SIZE.x, i * GRID_SIZE.y), GRID_SIZE);
        }
    }

    auto pScene = builder.build();
    scene = pScene.get();
    attachChild(std::move(pScene));
}

void Level::removeObject(const SceneNode &object) {
    scene->detachChild(object);
}

void Level::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
}

void Level::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
}

std::string Level::getClassName() const {
    return "Level";
}

bool Level::shouldSave() const {
    return true;
}
