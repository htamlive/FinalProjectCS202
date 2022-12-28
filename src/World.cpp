#include "World.h"
#include "Consts.h"
#include "SceneNode.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

class Grid : public SceneNode {
    sf::Vector2f sceneSize;
public:
    Grid(sf::Vector2f sceneSize) {
        this->sceneSize = sceneSize;
    }
    void updateCurrent(sf::Time dt) override {
    }
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override {
        for (int i = 0; i < sceneSize.x; i += GRID_SIZE.x) {
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(i, 0)),
                    sf::Vertex(sf::Vector2f(i, sceneSize.y))
            };
            target.draw(line, 2, sf::Lines);
        }

        for (int i = 0; i < sceneSize.y; i += GRID_SIZE.y) {
            sf::Vertex line[] = {
                    sf::Vertex(sf::Vector2f(0, i)),
                    sf::Vertex(sf::Vector2f(sceneSize.x, i))
            };
            target.draw(line, 2, sf::Lines);
        }
    }
};

World::World(sf::Vector2f sceneSize)
    : sceneSize(sceneSize) {
}

void World::init() {
    SceneNode::Ptr lv(new SceneNode());
    SceneNode::Ptr gl(new Grid(sceneSize));
    levelLayer = lv.get();
    gridLayer = gl.get();
    attachChild(std::move(lv));
    attachChild(std::move(gl));
    auto level = std::unique_ptr<Level>(new Level(currentLevelNumber + 1, sceneSize));
    currentLevel = level.get();
    levelLayer->attachChild(std::move(level));
    maintainedLevels.push_back(currentLevel);
}

void World::addNewLevel() {
    if (maintainedLevels.size() == 2) {
        levelLayer->detachChild(*maintainedLevels.front());
        maintainedLevels.pop_front();
    }
    currentLevelNumber++;
    oldLevel = currentLevel;
    auto level = std::unique_ptr<Level>(new Level(currentLevelNumber, sceneSize));
    currentLevel = level.get();
    level->move({0, currentLevelNumber*-sceneSize.y});
    levelLayer->attachChild(std::move(level));
    maintainedLevels.push_back(currentLevel);
}

void World::updateCurrent(sf::Time dt) {
}

void World::drawCurrent(sf::RenderTarget &target,
                        sf::RenderStates states) const {
}

Level* World::getCurrentLevel() const {
    return maintainedLevels.back();
}

void World::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
}

void World::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
}

std::string World::getClassName() const {
    return "World";
}

bool World::shouldSave() const {
    return true;
}
