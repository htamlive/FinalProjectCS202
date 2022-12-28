#include "Camera.h"
#include <SFML/Graphics/Rect.hpp>
#include <cmath>
#include <cstdlib>
#include <memory>
#include "AudioController.h"

Camera::Camera(SceneNode &follower, sf::RenderWindow &window, World &world)
    : follower(follower), window(window), world(world)
{
    futurePos = window.getView().getCenter();
    velocity = {0, 0};
    auto size = window.getView().getSize();
    auto wall1 = std::make_unique<Wall>(sf::FloatRect(-10, 0, 10, size.y));
    auto wall2 = std::make_unique<Wall>(sf::FloatRect(size.x, 0, 10, size.y));
    auto wall3 = std::make_unique<Wall>(sf::FloatRect(0, size.y, size.x, 10));
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
    if (playerPos.y + 15 < viewPos.y - viewSize.y / 2)
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
        AudioController::instance().removeStoppedSounds();
        world.addNewLevel();
        isTransitioning = true;
    }
    if (transitionTime.asSeconds() >= TRANSITION_TIME.asSeconds()) {
        isTransitioning = false;
        transitionTime = sf::Time::Zero;
        auto view = window.getView();
        view.setCenter({futurePos.x, futurePos.y});
        for (auto wall : walls) {
            wall->setPosition({
                0,
                view.getCenter().y - view.getSize().y / 2,
                });
        }
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

void Camera::save(std::ostream &out) {
    out << window.getView().getCenter().x << " " << window.getView().getCenter().y << endl;
    out << window.getView().getSize().x << " " << window.getView().getSize().y << endl;
}

void Camera::load(std::istream &in) {
    int x, y;
    int width, height;
    in >> x >> y;
    in >> width >> height;
    sf::View view;
    view.setCenter(x, y);
    view.setSize(width, height);
    window.setView(view);
}
