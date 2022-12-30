#include "GameLoader.h"
#include "Level.h"
#include "SpriteNode.h"
#include "Obstacle.h"
#include "SceneNode.h"
#include "World.h"
#include "Entity.h"
#include "Commuters.h"
#include "VehicleLaneController.h"
#include "AnimalLaneController.h"
#include "RoadLaneController.h"
#include "RiverController.h"
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <string>

void ignoreText(std::istream &in) {
    std::string line;
    while (true) {
        try {
            std::getline(in, line);
            std::stoi(line);
        } catch (std::exception &e) {
            std::cout << e.what() << std::endl;
            break;
        }
    }
}

std::unique_ptr<SceneNode> loadNode(std::istream &in) {
    std::string line;
    getline(in, line);
    std::unique_ptr<SceneNode> node;
    std::cout << "Loading " << line << std::endl;
    if (line == "SceneNode") {
        node = std::make_unique<SceneNode>();
        node->loadCurrentNode(in);
    } else if (line == "Entity") {
        node = std::make_unique<Entity>();
        node->loadCurrentNode(in);
    } else if (line == "World") {
        node = std::make_unique<World>();
        node->loadCurrentNode(in);
    } else if (line == "Player") {
        node = std::make_unique<Player>();
        node->loadCurrentNode(in);
    } else if (line == "Enemy") {
        node = std::make_unique<Enemy>();
        node->loadCurrentNode(in);
    } else if (line == "RiverController") {
        node = std::make_unique<RiverController>();
        node->loadCurrentNode(in);
    } else if (line == "SpriteNode") {
        node = std::make_unique<SpriteNode>(Texture::ID::Null);
        node->loadCurrentNode(in);
    } else if (line == "Level") {
        node = std::make_unique<Level>();
        node->loadCurrentNode(in);
    } else if (line == "WoodLane") {
        node = std::make_unique<WoodLane>();
        node->loadCurrentNode(in);
    } else if (line == "AnimalLane") {
        node = std::make_unique<AnimalLane>();
        node->loadCurrentNode(in);
    } else if (line == "VehicleLane") {
        node = std::make_unique<VehicleLane>();
        node->loadCurrentNode(in);
    } else if (line == "Vehicle") {
        node = std::make_unique<Vehicle>();
        node->loadCurrentNode(in);
    } else if (line == "VehicleLaneController") {
        node = std::make_unique<VehicleLaneController>();
        node->loadCurrentNode(in);
    } else if (line == "AnimalLaneController") {
        node = std::make_unique<AnimalLaneController>();
        node->loadCurrentNode(in);
    } else if (line == "Water") {
        node = std::make_unique<Water>();
        node->loadCurrentNode(in);
    } else if (line == "Rock") {
        node = std::make_unique<Rock>(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
        node->loadCurrentNode(in);
    } else if (line == "Light") {
        node = std::make_unique<Light>();
        node->loadCurrentNode(in);
    } else if (line == "Animal") {
        node = std::make_unique<Animal>();
        node->loadCurrentNode(in);
    } else if (line == "HealthBoost") {
        node = std::make_unique<HealthBoost>(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
        node->loadCurrentNode(in);
    } else if (line == "SmallSizeBoost") {
        node = std::make_unique<HealthBoost>(sf::Vector2f(0, 0), sf::Vector2f(0, 0));
        node->loadCurrentNode(in);
    } else if (line == "LevelLayer") {
        node = std::make_unique<LevelLayer>();
        node->loadCurrentNode(in);

    } else {
        throw std::runtime_error("Unhandle node type: " + line);
    }
    int n;
    in >> n;
    in.ignore();
    std::cout << "Loading " << n << " children" << std::endl;
    for (int j = 0; j < n; j++) {
        node->attachChild(loadNode(in));
    }
    node->onLoadingFinished();
    return node;
}
