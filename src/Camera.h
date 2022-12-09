#include "SceneNode.h"
#include "World.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

const sf::Time TRANSITION_TIME = sf::seconds(0.5f);

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
public:
    Camera(SceneNode &follower, sf::RenderWindow &window, World &world);
    void update(sf::Time dt);
};
