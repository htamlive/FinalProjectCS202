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
