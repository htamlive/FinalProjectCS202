#include "Level.h"
#include "Consts.h"
#include <numeric>
#include <random>

void Level::removeObject(const SceneNode &object) {
    detachChild(object);
}

void Level::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
}

void Level::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
    std::cout << "Level saved" << std::endl;
}

std::string Level::getClassName() const {
    return "Level";
}

bool Level::shouldSave() const {
    return true;
}
