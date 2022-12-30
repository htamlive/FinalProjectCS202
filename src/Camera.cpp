#include "Camera.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <cstdlib>
#include <memory>
#include <random>
#include "AudioController.h"

Camera::Camera(SceneNode &follower, sf::RenderWindow &window, World &world)
    : follower(follower), window(window), world(world)
{
    futurePos = window.getView().getCenter();
    transitionTime = sf::Time::Zero;
    isTransitioning = false;
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
    if (playerPos.y + 30 < viewPos.y - viewSize.y / 2)
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
    if (isShaking) {
        shakingUpdate(dt);
    }
}

void Camera::shakingUpdate(sf::Time dt) {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(-1, 1);
    if (shakeTime >= sf::seconds(0.1f)) {
        isShaking = false;
        shakeTime = sf::Time::Zero;
        auto view = window.getView();
        view.setCenter({balancePos.x, balancePos.y});
        window.setView(view);
        return;
    }
    auto view = window.getView();
    view.move(sf::Vector2f(dis(gen) * 4, dis(gen) * 1));
    window.setView(view);
    shakeTime += dt;
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
        return;
    }
    velocity = {length.x / dt.asSeconds(), length.y / dt.asSeconds()};
    for (auto wall : walls) {
        auto newView = window.getView();
        newView.setCenter({futurePos.x, futurePos.y});
        window.setView(newView);
        velocity = {0, 0};
        wall->setVelocity({0, 0});
        wall->setPosition({
            0,
            window.getView().getCenter().y - window.getView().getSize().y / 2,
            });
        transitionTime = sf::Time::Zero;
    }
}

void Camera::save(std::ostream &out) {
    out << window.getView().getCenter().x << " " << window.getView().getCenter().y << std::endl;
    out << window.getView().getSize().x << " " << window.getView().getSize().y << std::endl;
}

void Camera::load(std::istream &in) {
    int x, y;
    int width, height;
    in >> x >> y;
    in >> width >> height;
    sf::View view = window.getView();
    futurePos = {(float)x, (float)y};
    view.setCenter(x, y);
    view.setSize(width, height);
    window.setView(view);
}

void Camera::shake(sf::Time duration, float intensity) {
    balancePos = window.getView().getCenter();
    shakeTime = sf::Time::Zero;
    isShaking = true;
}
