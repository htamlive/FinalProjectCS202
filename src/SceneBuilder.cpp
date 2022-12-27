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

SceneBuilder &SceneBuilder::addRoadController(RoadLane::Type type, int lanes, float pos, float minSpeed, float maxSpeed,
                                              float minSpawnRate, float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto meanSpawnRate = (minSpawnRate + maxSpawnRate) / 2;

    std::unique_ptr<RoadLaneController> roads;
    switch (type) {
        case RoadLane::Type::Vehicle: {
            auto redRand = Random(std::uniform_real_distribution<>(MIN_RED_LIGHT_DURATION.asSeconds(),
                                                                   MAX_RED_LIGHT_DURATION.asSeconds()));
            auto greenRand = Random(std::uniform_real_distribution<>(MIN_GREEN_LIGHT_DURATION.asSeconds(),
                                                                     MAX_GREEN_LIGHT_DURATION.asSeconds()));
            auto vehicles = std::make_unique<VehicleLaneController>();
            vehicles->setGreenDuration(sf::seconds(greenRand.get<float>()));
            vehicles->setRedDuration(sf::seconds(redRand.get<float>()));
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
    roads->setFrequencyFunction([](double speed) {
        auto spawnRate = 400 / speed;
        return Random(std::normal_distribution<double>(spawnRate, spawnRate / 3));
    });
    roads->build();

    scene->attachChild(std::move(roads));
    return *this;

}

SceneBuilder &SceneBuilder::addRock(sf::Vector2f pos, sf::Vector2f size) {
    auto rock = std::make_unique<Rock>(pos, size);
    scene->attachChild(std::move(rock));
    return *this;
}

SceneBuilder &SceneBuilder::addBoost(sf::Vector2f pos, sf::Vector2f size) {
    std::unique_ptr<SceneNode> boost = nullptr;

    auto prob = Random(std::uniform_real_distribution(0.f, 1.f)).get<float>();
    for(auto &[type, rate] : BOOST_PROBS) {
        if (prob <= rate) {
            switch(type) {
            case Category::SmallSizeBoost:
                boost = std::make_unique<SmallSizeBoost>(pos, size);
                break;
            case Category::SpeedBoost:
                boost = std::make_unique<SpeedBoost>(pos, size);
                break;
            case Category::HealthBoost:
                boost = std::make_unique<HealthBoost>(pos, size);
                break;
            case Category::InvincibleBoost:
                boost = std::make_unique<InvincibleBoost>(pos, size);
                break;
            default:
                break;
            }
        } else
            prob -= rate;
    }

    scene->attachChild(std::move(boost));
    return *this;
}