#include "SceneNode.h"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cassert>

SceneNode::SceneNode() { mParent = nullptr; }

void SceneNode::attachChild(SceneNodePtr child) {
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::SceneNodePtr SceneNode::detachChild(const SceneNode &childTarget) {
    auto found = std::find_if(
            mChildren.begin(), mChildren.end(),
            [&](const SceneNodePtr &node) { return node.get() == &childTarget; });

    assert(found != mChildren.end());

    auto node = std::move(*found);
    mChildren.erase(found);
    node->mParent = nullptr;
    return node;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getTransform();

    drawCurrent(target, states);

    for (const auto &child: mChildren) {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateChildren(sf::Time dt) {
    for (auto &child: mChildren) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getAbsTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    const SceneNode *cur = this;
    while (cur) {
        transform *= cur->getTransform();
        cur = cur->mParent;
    }

    return transform;
}

sf::Vector2f SceneNode::getAbsPosition() const {
    return getAbsTransform() * sf::Vector2f();
}
