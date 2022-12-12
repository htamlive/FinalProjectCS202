#include "Camera.h"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <cstdlib>

Camera::Camera(SceneNode &follower, sf::RenderWindow &window, World &world)
    : follower(follower), window(window), world(world)
{
    futurePos = window.getView().getCenter();
    velocity = {0, 0};
}

Camera::~Camera() {
    window.setView(window.getDefaultView());
}
bool Camera::needReposition() {
    sf::View view = window.getView();
    sf::Vector2f playerPos = follower.getPosition();
    sf::Vector2f viewPos = view.getCenter();
    sf::Vector2f viewSize = view.getSize();
    if (playerPos.x < viewPos.x - viewSize.x / 2)
        return true;
    if (playerPos.x > viewPos.x + viewSize.x / 2)
        return true;
    if (playerPos.y < viewPos.y - viewSize.y / 2)
        return true;
    if (playerPos.y > viewPos.y + viewSize.y / 2)
        return true;
    return false;
}

void Camera::update(sf::Time dt) {
    auto view = window.getView();
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
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale = 1;
        velocity = velocity * scale;
        transitionTime += dt;

    } else if(dt != sf::seconds(0)) {
        velocity = {length.x / dt.asSeconds(), length.y / dt.asSeconds()};
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
