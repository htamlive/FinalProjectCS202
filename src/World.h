#pragma once
#include "Level.h"
#include "Player.h"
#include "SceneNode.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>
using std::list;

class LevelLayer : public SceneNode {
    sf::Vector2f sceneSize;
public:
    bool shouldSave() const override {
        return true;
    }
    std::string getClassName() const override {
        return "LevelLayer";
    }
};

/*
 * Represent the root node of the scene graph.
 */
class World : public SceneNode {
    SceneNode *levelLayer;
    SceneNode *gridLayer;
    Player *player = nullptr;
    list<Level *> maintainedLevels;
    Level *oldLevel;
    Level *currentLevel;
    int currentLevelNumber = 0;
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

    bool shouldSave() const override;

  public:
    World() = default;
    World(sf::Vector2f sceneSize);
    void init();
    void addNewLevel();
    void updateCurrent(sf::Time dt) override;
    Level* getCurrentLevel() const;
    void drawCurrent(sf::RenderTarget &target,
                     sf::RenderStates states) const override;
    void loadCurrentNode(std::istream &in = std::cin) override;
    void saveCurrentNode(std::ostream &out = std::cout) const override;
    void attachChild(Ptr child) override;
    std::string getClassName() const override;
};
