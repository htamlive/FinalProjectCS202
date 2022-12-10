#include "World.h"
#include "Consts.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <memory>

World::World(sf::Vector2f sceneSize)
    : sceneSize(sceneSize) {
    Level *level = new Level(currentLevelNumber + 1, sceneSize);
    attachChild(Ptr(level));
    currentLevel = level;
}

void World::addNewLevel() {
    if (maintainedLevels.size() == 2) {
        detachChild(*maintainedLevels.front());
        maintainedLevels.pop_front();
    }
    currentLevelNumber++;
    oldLevel = currentLevel;
    auto level = std::unique_ptr<Level>(new Level(currentLevelNumber, sceneSize));
    currentLevel = level.get();
    level->move({0, currentLevelNumber*-sceneSize.y});
    attachChild(std::move(level));
    maintainedLevels.push_back(currentLevel);
    cout << "Added new level" << endl;
    cout << "New level number: " << currentLevelNumber << endl;
    cout << "New level position: " << currentLevel->getPosition().x << ", "
         << currentLevel->getPosition().y << endl;
}

void World::updateCurrent(sf::Time dt) {
}
