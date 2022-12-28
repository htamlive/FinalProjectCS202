#include "SceneBuilder.h"
#include "AnimalLaneController.h"
#include "Enums.h"
#include "Obstacle.h"
#include "Random.h"
#include "RiverController.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "VehicleLaneController.h"
#include <SFML/Graphics/Sprite.hpp>

#include <SFML/System/Vector2.hpp>
#include <memory>

void incProb(vector<float> &prob, int index, float amount) {
    prob[index] += amount;
}

SceneBuilder::SceneBuilder(sf::Vector2f size) : sceneSize(size) {
    scene = std::make_unique<Level>();
}

std::unique_ptr<Level> SceneBuilder::build() { return std::move(scene); }

SceneBuilder &SceneBuilder::addBackground(Texture::ID id) {
    scene->attachChild(std::make_unique<SpriteNode>(id, sceneSize));
    return *this;
}

SceneBuilder &SceneBuilder::addRoadController(RoadLane::Type type, int lanes,
                                              float pos, float minSpeed,
                                              float maxSpeed,
                                              float minSpawnRate,
                                              float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;

    std::unique_ptr<RoadLaneController> roads;
    switch (type) {
    case RoadLane::Type::Vehicle: {
        auto vehicles = std::make_unique<VehicleLaneController>();
        // TODO: Handle traffic light durations
        vehicles->setGreenDuration(sf::seconds(10));
        vehicles->setRedDuration(sf::seconds(3));
        roads = std::move(vehicles);
        break;
    }
    case RoadLane::Type::Animal: {
        roads = std::make_unique<AnimalLaneController>();
        break;
    }
    case RoadLane::Type::River: {
        roads = std::make_unique<RiverController>();
        meanSpeed *= 0.6;
        break;
    }
    }

    auto speed = std::normal_distribution<double>(meanSpeed, meanSpeed / 4);
    roads->setLaneCount(lanes);
    roads->setPosY(pos);
    roads->setSpeedDistribution(speed);
    roads->build();

    scene->attachChild(std::move(roads));
    return *this;
}

SceneBuilder &SceneBuilder::addRock(sf::Vector2f pos, sf::Vector2f size) {
    auto rock = std::make_unique<Rock>(pos, size);
    scene->attachChild(std::move(rock));
    return *this;
}

SceneBuilder &SceneBuilder::addReward(sf::Vector2f pos, sf::Vector2f size) {
    auto reward = std::make_unique<HealthBoost>(pos, size);
    scene->attachChild(std::move(reward));
    return *this;
}

SceneBuilder &SceneBuilder::addBoost(sf::Vector2f pos) {
    auto boost = SceneNode::Ptr(new SpriteNode(Texture::Obstacle, pos));
    roadLayer->attachChild(std::move(boost));
    return *this;
}

DifficultyMetrics::DifficultyMetrics() {
    level = 1;
    minSpeed = BASE_MIN_SPEED;
    maxSpeed = BASE_MAX_SPEED;
    minSpawnRate = BASE_MIN_SPAWN_RATE;
    maxSpawnRate = BASE_MAX_SPAWN_RATE;
    laneSpawnProb = vector<float>(MAX_LANE_COUNT, .0f);
    float testSumProb =
        std::accumulate(laneSpawnProb.begin(), laneSpawnProb.end(), 0.0f);
}

DifficultyMetrics::DifficultyMetrics(int level) : DifficultyMetrics() {
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

void DifficultyMetrics::increaseLevel() {
    level++;
    minSpeed += BASE_SPEED_INCREASE;
    maxSpeed += BASE_SPEED_INCREASE;
    minSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    maxSpawnRate -= BASE_SPAWN_RATE_DECREASE;
    int toInc = level / 3;
    incProb(laneSpawnProb, toInc, 0.20f);
};

unique_ptr<Level> LevelGenerator::makeLevel(int level, sf::Vector2f sceneSize) {
    float mapWidth = sceneSize.x / GRID_SIZE.x;
    float mapHeight = sceneSize.y / GRID_SIZE.y;
    DifficultyMetrics difficultyMetrics(level);
    Random<std::discrete_distribution<unsigned>> random =
        std::discrete_distribution<unsigned>(
            difficultyMetrics.laneSpawnProb.begin(),
            difficultyMetrics.laneSpawnProb.end());
    auto builder = SceneBuilder(sceneSize);
    builder.addBackground(Texture::ID::Background);

    for (int i = 1; i < mapHeight - 2; i++) {
        float laneType;
        do {
            laneType = random.get<float>() + 1;
        } while (i + laneType >= mapHeight);

        auto prob = Random(std::uniform_real_distribution<float>(0.f, 1.f))
                        .get<float>();
        auto type = prob <= VEHICLE_LANE_PROB ? RoadLane::Type::Vehicle
                    : prob <= VEHICLE_LANE_PROB + ANIMAL_LANE_PROB
                        ? RoadLane::Type::Animal
                        : RoadLane::Type::River;
        builder.addRoadController(
            type, laneType, i * GRID_SIZE.y, difficultyMetrics.minSpeed,
            difficultyMetrics.maxSpeed, difficultyMetrics.minSpawnRate,
            difficultyMetrics.maxSpawnRate);
        auto shouldPlaceObstacle = Random(std::bernoulli_distribution(0.2));
        auto shouldPlaceReward = Random(std::bernoulli_distribution(0.05));
        for (int j = 0; j < laneType; j++) {
            for (int k = 0; k < mapWidth; k++) {
                if (shouldPlaceReward.get<bool>()) {
                    builder.addReward({k * GRID_SIZE.x, (i + j) * GRID_SIZE.y},
                                      GRID_SIZE);
                }
            }
        }
        i += laneType;
        if (i >= mapHeight - 2) {
            break;
        }
        for (int j = 0; j < mapWidth; j++) {
            if (shouldPlaceObstacle.get<bool>())
                builder.addRock(sf::Vector2f(j * GRID_SIZE.x, i * GRID_SIZE.y),
                                GRID_SIZE);
        }
    }

    std::unique_ptr<Level> pScene = builder.build();
    return pScene;
}
