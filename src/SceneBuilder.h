#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

#include "Lane.h"
#include "SceneNode.h"
using namespace std;

class SceneBuilder {
    sf::Vector2f sceneSize;
    SceneNode::Ptr scene;
    SceneNode *roadLayer;
    SceneNode *backgroundLayer;

  public:
    SceneBuilder(sf::Vector2f size);
    SceneBuilder &addBackground(Texture::ID id);
    SceneBuilder &addRoad(int lanes, float pos, float minSpeed,
                                        float maxSpeed, float minSpawnRate,
                                        float maxSpawnRate);
    SceneNode::Ptr build();
};
