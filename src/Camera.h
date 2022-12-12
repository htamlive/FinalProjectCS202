#include "SceneNode.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

const sf::Time TRANSITION_TIME = sf::seconds(0.5f);

class Wall : public SceneNode {
    sf::FloatRect bounds;
    sf::Vector2f velocity;
public:
    Wall(sf::FloatRect bounds) : bounds(bounds) {
    }
    sf::FloatRect getLocalBounds() const override {
        return bounds;
    }
    void updateCurrent(sf::Time dt) override {
        move(velocity * dt.asSeconds());
    }
    void setVelocity(sf::Vector2f velocity) {
        this->velocity = velocity;
    }
};


class Camera {
    sf::Vector2f velocity;
    sf::Vector2f futurePos;
    bool isTransitioning = false;
    sf::Time transitionTime = sf::seconds(0);

    SceneNode &follower;
    sf::RenderWindow &window;
    World &world;

    bool needReposition();
    void reposition();
    void updateVelocity(sf::Time dt);
    vector<Wall*> walls;
public:
    Camera(SceneNode &follower, sf::RenderWindow &window, World &world);
    ~Camera();
    void update(sf::Time dt);
};
