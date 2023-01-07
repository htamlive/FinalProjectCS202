#include "World.h"
#include "Consts.h"
#include "LevelGenerator.h"
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
    SceneNode::Ptr lv(new LevelLayer());
    SceneNode::Ptr gl(new Grid(sceneSize));
    gridLayer = gl.get();
    attachChild(std::move(gl));
    auto level = LevelGenerator().makeLevel(1, sceneSize);
    attachChild(std::move(level));
}

void World::addNewLevel() {
    if (maintainedLevels.size() == 2) {
        detachChild(*maintainedLevels.front());
        maintainedLevels.pop_front();
    }
    currentLevelNumber++;
    oldLevel = currentLevel;
    auto level = LevelGenerator().makeLevel(currentLevelNumber, sceneSize);
    currentLevel = level.get();
    level->move({0, currentLevelNumber*(-sceneSize.y)});
    attachChild(std::move(level));
    auto p = detachChild(*player);
    attachChild(std::move(p));
}

void World::updateCurrent(sf::Time dt) {
}

void World::drawCurrent(sf::RenderTarget &target,
                        sf::RenderStates states) const {
}

Level* World::getCurrentLevel() const {
    return currentLevel;
}

void World::loadCurrentNode(std::istream &in) {
    SceneNode::loadCurrentNode(in);
    in >> currentLevelNumber;
    in >> sceneSize.x >> sceneSize.y;
    sceneSize *= SYSTEM_SCALE;
}

void World::saveCurrentNode(std::ostream &out) const {
    SceneNode::saveCurrentNode(out);
    out << currentLevelNumber << std::endl;
    out << sceneSize.x/SYSTEM_SCALE << " " << sceneSize.y/SYSTEM_SCALE << std::endl;
}

std::string World::getClassName() const {
    return "World";
}

bool World::shouldSave() const {
    return true;
}

void World::attachChild(Ptr child) {

    if (auto result = dynamic_cast<Level *>(child.get())) {
        std::cout << "Level attached" << std::endl;
        maintainedLevels.push_back(result);
        currentLevel = maintainedLevels.back();
    } else if (auto result = dynamic_cast<Player *>(child.get())) {
        std::cout << "Player attached" << std::endl;
        player = result;
    }
    SceneNode::attachChild(std::move(child));
}
