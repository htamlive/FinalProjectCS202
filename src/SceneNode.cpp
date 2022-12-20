#include "SceneNode.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <cassert>

SceneNode::SceneNode() { mParent = nullptr; }

void SceneNode::attachChild(Ptr child) {
    if (debug && applyDebugToChildren) {
        child->setDebug(true, true);
    }
    child->mParent = this;
    mChildren.push_back(std::move(child));
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode &childTarget) {
    auto found =
        std::find_if(mChildren.begin(), mChildren.end(), [&](const Ptr &node) {
            return node.get() == &childTarget;
        });

    assert(found != mChildren.end());

    auto node = std::move(*found);
    mChildren.erase(found);
    node->mParent = nullptr;
    return node;
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= this->getTransform();

    drawCurrent(target, states);
    if (debug) {
        drawBoundingBox(target, states);
    }

    for (const auto &child : mChildren) {
        child->draw(target, states);
    }
}

void SceneNode::update(sf::Time dt) {
    updateCurrent(dt);
    updateChildren(dt);
}

void SceneNode::updateChildren(sf::Time dt) {
    for (auto &child : mChildren) {
        child->update(dt);
    }
}

sf::Transform SceneNode::getAbsTransform() const {
    sf::Transform transform = sf::Transform::Identity;
    const SceneNode *cur = this;
    while (cur) {
        assert(cur);
        transform *= cur->getTransform();
        cur = cur->mParent;
    }

    return transform;
}

sf::Vector2f SceneNode::getAbsPosition() const {
    return getAbsTransform() * sf::Vector2f();
}

void SceneNode::checkNodeCollision(SceneNode &node,
                                   std::set<Pair> &collisions) {
    if (this != &node && checkCollision(*this, node)) {
        collisions.insert(std::minmax(this, &node));
    }

    for (const auto &child : mChildren) {
        child->checkNodeCollision(node, collisions);
    }
}

void SceneNode::checkSceneCollision(SceneNode &node,
                                    std::set<Pair> &collisions) {
    checkNodeCollision(node, collisions);

    for (const auto &child : node.mChildren) {
        checkSceneCollision(*child, collisions);
    }
}

bool checkCollision(const SceneNode &lnode, const SceneNode &rnode) {
    return lnode.getBoundingRect().intersects(rnode.getBoundingRect());
}

sf::FloatRect SceneNode::getBoundingRect() const {
    return getAbsTransform().transformRect(getLocalBounds());
}

sf::FloatRect SceneNode::getLocalBounds() const {
    return sf::FloatRect();
}

void SceneNode::drawCurrent(sf::RenderTarget &target,
                            sf::RenderStates states) const {}

void SceneNode::updateCurrent(sf::Time dt) {}

void SceneNode::drawBoundingBox(sf::RenderTarget &target,
                                sf::RenderStates states) const {
    sf::FloatRect rect = getLocalBounds();
    sf::RectangleShape shape;
    shape.setPosition(rect.left, rect.top);
    shape.setSize(sf::Vector2f(rect.width, rect.height));
    shape.setFillColor(sf::Color::Transparent);
    shape.setOutlineColor(sf::Color::Red);
    shape.setOutlineThickness(1.f);
    target.draw(shape, states);
}

void SceneNode::setDebug(bool on, bool recursive) {
    debug = on;
    applyDebugToChildren = recursive;
    if (recursive) {
        for (auto &child : mChildren) {
            child->setDebug(on, recursive);
        }
    }
}

Category::Type SceneNode::getCategory() const {
    return Category::Type::None;
}

void SceneNode::saveInternal(std::ostream& out) const {
    out << getPosition().x << " " << getPosition().y << std::endl;
    out << getScale().x << " " << getScale().y << std::endl;
    out << getRotation() << std::endl;
}

void SceneNode::loadCurrentNode(std::istream& in) {
    float x, y;
    float scaleX, scaleY;
    float rotation;
    // position
    in >> x >> y;
    setPosition(x, y);
    // scale
    in >> scaleX >> scaleY;
    setScale(scaleX, scaleY);
    // rotation
    in >> rotation;
    setRotation(rotation);
}

void SceneNode::saveNode(std::ostream& out) const {
    saveCurrentNode(out);
    out << mChildren.size() << std::endl;
    for (const auto& child : mChildren) {
        child->saveNode(out);
    }
}

void SceneNode::saveCurrentNode(std::ostream& out) const {
    out << "SceneNode" << std::endl;
    saveInternal(out);
}
