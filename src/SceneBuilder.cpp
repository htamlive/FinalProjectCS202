#include "SceneBuilder.h"
#include "Enums.h"
#include "RoadLanes.h"
#include "SceneNode.h"
#include "Obstacle.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

SceneBuilder::SceneBuilder(sf::Vector2f size) : sceneSize(size) {
    scene           = SceneNode::Ptr(new SceneNode());
    auto bg         = SceneNode::Ptr(new SceneNode());
    auto road       = SceneNode::Ptr(new SceneNode());
    backgroundLayer = bg.get();
    roadLayer       = road.get();
    scene->attachChild(std::move(bg));
    scene->attachChild(std::move(road));
}

SceneNode::Ptr SceneBuilder::build() { return std::move(scene); }

SceneBuilder &SceneBuilder::addBackground(Texture::ID id) {
    backgroundLayer->attachChild(SceneNode::Ptr(new SpriteNode(id, sceneSize)));
    return *this;
}

SceneBuilder &SceneBuilder::addRoad(int lanes, float pos, float minSpeed,
                                    float maxSpeed, float minSpawnRate,
                                    float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;
    auto speed = std::normal_distribution<double>(meanSpeed, meanSpeed / 4);
    // TODO: Handle random spawn rate
    auto roads = std::make_unique<RoadLanes>(
        RoadLane::Type::Vehicle, lanes, pos, speed, [](double speed) {
            auto spawnRate = 400 / speed;
            return Random(std::normal_distribution<double>(spawnRate, spawnRate / 3));
        });

    roadLayer->attachChild(std::move(roads));
    return *this;
}

SceneBuilder &SceneBuilder::addObstacle(sf::Vector2f pos) {
    auto obstacle = std::unique_ptr<Obstacle>(new Obstacle(pos));
    roadLayer->attachChild(std::move(obstacle));
    return *this;
}

SceneBuilder &SceneBuilder::addReward(sf::Vector2f pos) {
    auto reward = std::unique_ptr<Reward>(new Reward(pos));
    roadLayer->attachChild(std::move(reward));
    return *this;
}

SceneBuilder &SceneBuilder::addBoost(sf::Vector2f pos) {
    auto boost = SceneNode::Ptr(new SpriteNode(Texture::Obstacle, pos));
    roadLayer->attachChild(std::move(boost));
    return *this;
}
