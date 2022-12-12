#include "SceneBuilder.h"
#include "Entity.h"
#include "RoadLanes.h"
#include "SceneNode.h"
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

SceneNode::Ptr SceneBuilder::build() { return std::move(scene); }

SceneBuilder &SceneBuilder::addBackground(Texture::ID id) {
    backgroundLayer->attachChild(SceneNode::Ptr(new SpriteNode(id, sceneSize)));
    return *this;
}

SceneBuilder &SceneBuilder::addRoad(int lanes, float pos, float minSpeed,
                                    float maxSpeed, float minSpawnRate,
                                    float maxSpawnRate) {
    auto meanSpeed = (minSpeed + maxSpeed) / 2;
    auto speed =
        std::normal_distribution<double>(meanSpeed, meanSpeed / 2);
    // TODO: Handle random spawn rate
    auto roads = std::make_unique<RoadLanes>(
        RoadLane::Type::Vehicle, lanes, pos,
        speed, [](double i) {
            return Random(std::normal_distribution<double>(3.0, 1.0));
        });

    roadLayer->attachChild(std::move(roads));
    return *this;
}
