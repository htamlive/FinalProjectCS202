#include "Camera.h"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <cstdlib>

Camera::Camera(SceneNode &follower, sf::RenderWindow &window, World &world)
    : follower(follower), window(window), world(world)
{
    futurePos = window.getView().getCenter();
    velocity = {0, 0};
    auto size = window.getView().getSize();
    auto wall1 = std::unique_ptr<Wall>(new Wall(sf::FloatRect(-10, 0, 10, size.y)));
    auto wall2 = std::unique_ptr<Wall>(new Wall(sf::FloatRect(size.x, 0, 10, size.y)));
    auto wall3 = std::unique_ptr<Wall>(new Wall(sf::FloatRect(0, size.y, size.x, 10)));
    walls.push_back(wall1.get());
    walls.push_back(wall2.get());
    walls.push_back(wall3.get());
    world.attachChild(std::move(wall1));
    world.attachChild(std::move(wall2));
    world.attachChild(std::move(wall3));
}

Camera::~Camera() {
    window.setView(window.getDefaultView());
}
bool Camera::needReposition() {
    sf::View view = window.getView();
    sf::Vector2f playerPos = follower.getAbsPosition();
    sf::Vector2f viewPos = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    // Add a little bit of offset to the view size to make sure the player is always in the view
    if (playerPos.y + 10 < viewPos.y - viewSize.y / 2)
        return true;
    return false;
}

void Camera::update(sf::Time dt) {
    auto view = window.getView();
    auto size = view.getSize();
    view.move(velocity * dt.asSeconds());
    window.setView(view);
    updateVelocity(dt);
    if (needReposition() && !isTransitioning) {
        futurePos = {
            window.getView().getCenter().x,
            window.getView().getCenter().y - window.getView().getSize().y,
        };
        world.addNewLevel();
        isTransitioning = true;
    }
    if (transitionTime.asSeconds() >= TRANSITION_TIME.asSeconds()) {
        for (auto wall : walls) {
            wall->setVelocity(sf::Vector2f(0, 0));
        }
        isTransitioning = false;
        transitionTime = sf::Time::Zero;
        auto view = window.getView();
        view.setCenter({round(futurePos.x), round(futurePos.y)});
        window.setView(view);
    }
}

void Camera::updateVelocity(sf::Time dt) {
    auto length = futurePos - window.getView().getCenter();
    if (isTransitioning) {
        auto time_left = TRANSITION_TIME - transitionTime;
        velocity = {length.x / time_left.asSeconds(), length.y / time_left.asSeconds()};
        for (auto wall : walls) {
            wall->setVelocity(velocity);
        }
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale = 1;
        velocity = velocity * scale;
        transitionTime += dt;

    } else if(dt != sf::seconds(0)) {
        velocity = {length.x / dt.asSeconds(), length.y / dt.asSeconds()};
        for (auto wall : walls) {
            wall->setVelocity(velocity);
        }
    }

    // if (isTransitioning) {
    //     auto time_left = TRANSITION_TIME - transitionTime;
    //     velocity = {0, 5};
    //     transitionTime += dt;
    //     cout << "transitionTime: " << transitionTime.asSeconds() << endl;
    // } else {
    //     velocity = {0, 0};
    // }
}

void Camera::reposition() {
}
