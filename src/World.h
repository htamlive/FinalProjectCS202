#pragma once
#include "SceneNode.h"
#include "Player.h"
#include "Level.h"
#include "Consts.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>

/*
 * Represent the root node of the scene graph.
 */
class World : public SceneNode {
    Level *oldLevel;
    Level *currentLevel;
    int currentLevelNumber = 0;
    Player &player;
    sf::Vector2f sceneSize;
    bool levelTransitioning = false;
    bool outOfView = false;

    /**
     * Helper function to convert real coordinates to world coordinates.
     * @param realCoord
     */
    sf::Vector2f worldCoordToRealCoord(sf::Vector2i worldCoord);

    /**
     * Helper function to convert world coordinates to real coordinates.
     */
    sf::Vector2i realCoordToWorldCoord(sf::Vector2f realCoord);

    void makeLevelTransition();
public:
    World(Player &player, sf::Vector2f sceneSize);
    void addNewLevel();
    void updateCurrent(sf::Time dt) override;
};
