#include "Lane.h"
#include "Animal.h"
#include "Vehicle.h"
#include <iostream>

Lane::Lane()
    : type(Type::Vehicle), laneTexture(), height(0), velocity(0, 0),
      frequency() {}

Lane::Lane(Lane::Type type, Texture::ID commuterTexture,
           Texture::ID laneTexture, float y, float laneHeight,
           float commuterWidth, float commuterHeight, Lane::Direction direction,
           float speed, Random<std::normal_distribution<double>> frequency)
    : type(type), laneTexture(laneTexture), height(laneHeight),
      frequency(frequency) {
    setPosition(0, y);

    velocity = direction == Direction::Right ? sf::Vector2f(speed, 0)
                                             : sf::Vector2f(-speed, 0);

    newCommuter = [this, direction, commuterWidth, type, commuterHeight,
                   commuterTexture]() -> std::unique_ptr<Entity> {
        auto pos =
            direction == Direction::Right
                ? sf::Vector2f(0, getPosition().y)
                : sf::Vector2f((float)WINDOW_VIDEO_MODE.width - commuterWidth,
                               getPosition().y);
        if (type == Type::Vehicle) {
            return std::make_unique<Vehicle>(velocity, pos.x, pos.y,
                                             commuterWidth, commuterHeight,
                                             commuterTexture);
        } else {
            return std::make_unique<Animal>(velocity, pos.x, pos.y,
                                            commuterWidth, commuterHeight,
                                            commuterTexture);
        }
    };
}

void Lane::updateCurrent(sf::Time dt) {
    timer -= dt;
    if (timer <= sf::Time::Zero) {
        // Add a new vehicle
        std::cout << "New commuter" << std::endl;
        auto commuter = newCommuter();
        commuters.push_back(commuter.get());
        attachChild(std::move(commuter));
        timer = sf::seconds(frequency.get<float>());
    }

    // Remove vehicles out of screen
    while (!commuters.empty() && commuters.front()->isOutOfScreen()) {
        std::cout << "Remove commuter" << std::endl;
        detachChild(*commuters.front());
        commuters.pop_front();
    }
}

void Lane::drawCurrent(sf::RenderTarget &target,
                       sf::RenderStates states) const {
    sf::Sprite sprite(TextureHolder::instance().get(laneTexture).texture);
    // Set scale to match the height of the road
    auto scaleFactor = height / (float)sprite.getTexture()->getSize().y;
    sprite.setScale(scaleFactor, scaleFactor);

    for (float i = 0; i < (float)WINDOW_VIDEO_MODE.width;
         i += sprite.getLocalBounds().width) {
        sprite.setPosition(i, getPosition().y);
        target.draw(sprite, states);
    }
}

void Lane::onLightChanged() {
    if (type == Type::Vehicle) {
        for (auto &vehicle : commuters) {
            dynamic_cast<Vehicle *>(vehicle)->onLightChanged();
        }
    }
}
