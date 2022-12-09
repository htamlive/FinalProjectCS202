#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "SceneNode.h"
#include "Lane.h"
using namespace std;

class SceneBuilder {
    SceneNode::Ptr scene;
    SceneNode* roadLayer;
    SceneNode* backgroundLayer;
public:
    SceneBuilder(sf::Vector2f size);
    SceneBuilder& addBackground(Texture::ID id);
    SceneBuilder& addRoad(int type, float pos);
    SceneNode::Ptr build();
};
