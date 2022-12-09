#include "SceneBuilder.h"
#include "Entity.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>

SceneBuilder::SceneBuilder(sf::Vector2f size) {
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
        SceneNode::Ptr(new SpriteNode(id, {800, 600})));
    return *this;
}
SceneBuilder &SceneBuilder::addRoad(int type, float pos) { return *this; }
