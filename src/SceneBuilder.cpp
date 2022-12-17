#include "SceneBuilder.h"
#include "Enums.h"
#include "VehicleLaneController.h"
#include "AnimalLaneController.h"
#include "RiverController.h"
#include "SceneNode.h"
#include "Obstacle.h"
#include <SFML/Graphics/Sprite.hpp>
#include "SpriteNode.h"

#include <memory>

SceneBuilder::SceneBuilder(sf::Vector2f size) : sceneSize(size) {
    scene           = std::make_unique<SceneNode>();
    auto bg         = std::make_unique<SceneNode>();
    auto road       = std::make_unique<SceneNode>();
    backgroundLayer = bg.get();
    roadLayer       = road.get();
    scene->attachChild(std::move(bg));
    scene->attachChild(std::move(road));
}

SceneNode::Ptr SceneBuilder::build() { return std::move(scene); }

SceneBuilder &SceneBuilder::addBackground(Texture::ID id) {
    backgroundLayer->attachChild(std::make_unique<SpriteNode>(id, sceneSize));
    return *this;
}

SceneBuilder &SceneBuilder::addVehicleRoad(int lanes, float pos, float minSpeed,
                                           float maxSpeed, float minSpawnRate,
                                           float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;
    auto speed = std::normal_distribution<double>(meanSpeed, meanSpeed / 4);
    // TODO: Handle traffic light durations
    auto roads = std::make_unique<VehicleLaneController>(
        lanes, pos,
        speed, [](double speed) {
                auto spawnRate = 400 / speed;
                return Random(std::normal_distribution<double>(spawnRate, spawnRate / 3));
            },
        sf::seconds(10), sf::seconds(3));
    roads->build();

    scene->attachChild(std::move(roads));
    return *this;
}

SceneBuilder &SceneBuilder::addAnimalRoad(int lanes, float pos, float minSpeed, float maxSpeed, float minSpawnRate,
                                          float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;
    auto speed = std::normal_distribution<double>(meanSpeed, meanSpeed / 4);
    auto roads = std::make_unique<AnimalLaneController>(
            lanes, pos,
            speed, [](double speed) {
                auto spawnRate = 400 / speed;
                return Random(std::normal_distribution<double>(spawnRate, spawnRate / 3));
            });
    roads->build();

    scene->attachChild(std::move(roads));
    return *this;
}

SceneBuilder &SceneBuilder::addRiverRoad(int lanes, float pos, float minSpeed, float maxSpeed, float minSpawnRate,
                                         float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;
    auto speed = std::normal_distribution<double>(meanSpeed, meanSpeed / 4);
    auto roads = std::make_unique<RiverController>(
            lanes, pos,
            speed, [](double speed) {
                auto spawnRate = 400 / speed;
                return Random(std::normal_distribution<double>(spawnRate, spawnRate / 3));
            });
    roads->build();

    scene->attachChild(std::move(roads));
    return *this;
}


SceneBuilder &SceneBuilder::addObstacle(sf::Vector2f pos, sf::Vector2f size) {
    auto obstacle = std::make_unique<Obstacle>(pos, size);
    scene->attachChild(std::move(obstacle));
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