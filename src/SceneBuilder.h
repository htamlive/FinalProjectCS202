#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Lane.h"
#include "Level.h"
#include "RoadLane.h"
#include "SceneNode.h"

using namespace std;

/**
 * @breif Provide basic tools to add elements to the scene
 */
class SceneBuilder {
    sf::Vector2f sceneSize;
    std::unique_ptr<Level> scene;
    std::unique_ptr<SceneNode> bg;
    SceneNode *roadLayer;
    SceneNode *backgroundLayer;

  public:
    SceneBuilder(sf::Vector2f size);
    SceneBuilder &addBackground(Texture::ID id);
    SceneBuilder &addRoadController(RoadLane::Type type, int lanes, float pos,
                                    float minSpeed, float maxSpeed,
                                    float minSpawnRate, float maxSpawnRate);

    SceneBuilder &addRock(sf::Vector2f pos, sf::Vector2f size);
    SceneBuilder &addReward(sf::Vector2f pos, sf::Vector2f size);
    SceneBuilder &addBoost(sf::Vector2f pos);
    SceneBuilder &addBombard(sf::Vector2f pos);
    SceneBuilder &addElectricGate(sf::Vector2f pos, float width);
    SceneBuilder &addTree(sf::Vector2f pos);
    SceneBuilder &addHouse(sf::Vector2f pos);
    SceneBuilder &addHole(sf::Vector2f pos);
    SceneBuilder &addMudHole(sf::Vector2f pos);
    std::unique_ptr<Level> build();
};
