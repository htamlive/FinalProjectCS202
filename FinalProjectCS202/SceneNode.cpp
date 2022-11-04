#include "SceneNode.h"
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

    for (const auto& child: mChildren) {
        child->draw(target, states);
    }
}
