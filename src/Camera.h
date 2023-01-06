#include "Enums.h"
#include "SceneNode.h"
#include "World.h"
#include "PlayerCollidable.h"
#include "PlayerState.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

using std::vector;

const sf::Time TRANSITION_TIME = sf::seconds(0.5f);

class Wall : public PlayerCollidable {
private:
    sf::Vector2f velocity;
    sf::FloatRect bounds;

    void onStartPlayerCollision() override {
        sf::Vector2f direction = -player->getDirectionVec();
        if (bounds.width < bounds.height) {
            direction.y = -direction.y;
        } else {
            direction.x = -direction.x;
        }
        auto newPos = player->getPosition() + direction * (GRID_SIZE.x / 2.f);
        player->setState(new CollidingState(player, newPos));
    }

public:
    Wall(sf::FloatRect bounds) : bounds(bounds) {}

    sf::FloatRect getLocalBounds() const override {
        return bounds;
    }

    void setVelocity(sf::Vector2f velocity) {
        this->velocity = velocity;
    }

    void updateCurrent(sf::Time dt) override {
        move(velocity * dt.asSeconds());
        PlayerCollidable::updateCurrent(dt);
    }
};


class Camera {
    sf::Vector2f balancePos;
    sf::Vector2f velocity;
    sf::Vector2f futurePos;
    bool isTransitioning = false;
    sf::Time transitionTime = sf::seconds(0);

    SceneNode &follower;
    sf::RenderWindow &window;
    World &world;
    bool isShaking = false;
    sf::Time shakeTime = sf::seconds(0);

    bool needReposition();
    void reposition();
    void updateVelocity(sf::Time dt);
    void shakingUpdate(sf::Time dt);
    vector<Wall*> walls;
public:
    Camera(SceneNode &follower, sf::RenderWindow &window, World &world);
    ~Camera();

    void save(std::ostream &out);
    void load(std::istream &in);
    void update(sf::Time dt);
    void shake(sf::Time duration, float intensity);
    bool checkIsTransistioning() {
        return this->isTransitioning;
    }
};
