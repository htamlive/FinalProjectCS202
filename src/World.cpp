#include "World.h"
#include "Consts.h"
#include <SFML/System/Vector2.hpp>
#include <iostream>

World::World(Player &player, sf::Vector2f sceneSize)
    : player(player), sceneSize(sceneSize) {
    Level *level = new Level(currentLevelNumber, sceneSize);
    attachChild(Ptr(level));
    currentLevel = level;
}

void World::addNewLevel() {
    currentLevelNumber++;
    oldLevel = currentLevel;
    Level *level = new Level(currentLevelNumber, sceneSize);
    currentLevel = level;
    level->move({0, currentLevelNumber*-sceneSize.y});
    attachChild(Ptr(level));
    cout << "Added new level" << endl;
    cout << "New level number: " << currentLevelNumber << endl;
    cout << "New level position: " << currentLevel->getPosition().x << ", "
         << currentLevel->getPosition().y << endl;
}

void World::updateCurrent(sf::Time dt) {
}
