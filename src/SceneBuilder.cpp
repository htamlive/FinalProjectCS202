#include "SceneBuilder.h"
#include "Entity.h"
#include "SceneNode.h"
#include "RoadLanes.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

SceneBuilder::SceneBuilder(sf::Vector2f size) : sceneSize(size) {
    scene = SceneNode::Ptr(new SceneNode());
    auto bg = SceneNode::Ptr(new SceneNode());
    auto road = SceneNode::Ptr(new SceneNode());
    backgroundLayer = bg.get();
    roadLayer = road.get();
    scene->attachChild(std::move(bg));
    scene->attachChild(std::move(road));
}

SceneNode::Ptr SceneBuilder::build() {
    return std::move(scene);
}

SceneBuilder &SceneBuilder::addBackground(Texture::ID id) {
    backgroundLayer->attachChild(
        SceneNode::Ptr(new SpriteNode(id, sceneSize)));
    return *this;
}
SceneBuilder &SceneBuilder::addRoad(int lanes, float pos) {
    auto roads = std::make_unique<RoadLanes>(
           RoadLane::Type::Vehicle, lanes, pos,
           Random(std::normal_distribution<double>(100, 10.0)),
           [](double i) {
               return Random(std::normal_distribution<double>(3.0, 1.0));
           });

    roadLayer->attachChild(std::move(roads));
    return *this;
}
