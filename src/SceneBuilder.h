#pragma once
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneNode.h"
#include "Lane.h"
using namespace std;

class SceneBuilder {
    sf::Vector2f sceneSize;
    SceneNode::Ptr scene;
    SceneNode* roadLayer;
    SceneNode* backgroundLayer;
public:
    SceneBuilder(sf::Vector2f size);
    SceneBuilder& addBackground(Texture::ID id);
    SceneBuilder& addRoad(int type, float pos);
    SceneNode::Ptr build();
};
