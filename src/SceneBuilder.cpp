#include "SceneBuilder.h"
#include "AnimalLaneController.h"
#include "Enums.h"
#include "Obstacle.h"
#include "Random.h"
#include "RiverController.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "VehicleLaneController.h"
#include "Pickups.h"

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
    bool found = false;
    for(auto &[type, rate] : BOOST_PROBS) {
        if (found) break;
        if (prob <= rate) {
            found = true;
            switch(type) {
            case Category::SmallSizePickup:
                boost = std::make_unique<SmallSizePickup>(pos, size);
                break;
            case Category::SpeedPickup:
                boost = std::make_unique<SpeedPickup>(pos, size);
                break;
            case Category::HealthPickup:
                boost = std::make_unique<HealthPickup>(pos, size);
                break;
            case Category::InvinciblePickup:
                boost = std::make_unique<InvinciblePickup>(pos, size);
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
