#include "Enums.h"
#include "Lane.h"
#include "LaneController.h"
#include "Random.h"
#include "SceneNode.h"
#include "TextureHolder.h"
#include <SFML/Graphics.hpp>
#include <functional>
#include <memory>
#include <random>

int main() {
    TextureHolder::instance().load(Texture::ID::Vehicle,
                                   "../resources/images/greenCar.png");
    TextureHolder::instance().load(Texture::ID::Animal,
                                   "../resources/images/greenCar.png");
    TextureHolder::instance().load(Texture::ID::Road,
                                   "../resources/images/VehicleRoad.png",
                                   {32, 32}, 9, 3);
    TextureHolder::instance().load(Texture::ID::BotLane,
                                   "../resources/images/VehicleRoad.png",
                                   {32, 32}, 9, 3);
    TextureHolder::instance().load(Texture::ID::TopLane,
                                   "../resources/images/VehicleRoad.png",
                                   {32, 32}, 9, 3);
    std::function<Random<std::normal_distribution<double>>(double)>
        randomFunction = [](double i) {
            return Random(std::normal_distribution<double>(1, 0.5));
        };
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
    auto laneController = std::make_unique<LaneController>(
        Lane::Type::Vehicle, 1, 400, 40, 40, 40,
        Random(std::normal_distribution<double>(1, 0.5)), randomFunction);
    SceneNode root;
    // auto lane = std::make_unique<Lane>(
    //     Lane::Type::Vehicle, Texture::ID::Vehicle, Texture::ID::Road, 200,
    //     60, 40, 40, Lane::Direction::Right, 60,
    //     Random(std::normal_distribution<double>(3.0, 1.0)));

    root.attachChild(std::move(laneController));
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        sf::Time dt = clock.restart();

        window.clear(sf::Color::White);
        root.update(dt);
        window.draw(root);
        window.display();
    }

    return 0;
}
