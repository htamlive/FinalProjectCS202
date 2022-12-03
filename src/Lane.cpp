#include "Lane.h"
#include "Animal.h"
#include "Vehicle.h"
#include <iostream>

Lane::Lane()
        : type(Type::Vehicle), laneTexture(), height(0), velocityX(0),
          frequency(), commuterTexture(), commuterSize(0, 0) {}

Lane::Lane(Lane::Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float speed,
           Random<std::normal_distribution<double>> frequency) : type(type), frequency(frequency),
                                                                 laneTexture(laneTexture), height(DEF_LANE_HEIGHT),
                                                                 velocityX(-speed), commuterTexture(commuterTexture), commuterSize(DEF_COMMUTER_SIZE) {
    setPosition(0, y);
}

Lane::Lane(Lane::Type type, Texture::ID commuterTexture,
           Texture::ID laneTexture, float y, float laneHeight,
           float commuterWidth, float commuterHeight, Lane::Direction direction,
           float speed, Random<std::normal_distribution<double>> frequency)
        : type(type), laneTexture(laneTexture), height(laneHeight),
          frequency(frequency), commuterTexture(commuterTexture), commuterSize(commuterWidth, commuterHeight) {
    setPosition(0, y);

    velocityX = direction == Direction::Right ? speed : -speed;
}

std::unique_ptr<Entity> Lane::newCommuter() const {
    auto pos =
            velocityX > 0
            ? sf::Vector2f(-commuterSize.x + 1, 0)
            : sf::Vector2f((float) WINDOW_VIDEO_MODE.width - 1, 0);
    if (type == Type::Vehicle) {
        return std::make_unique<Vehicle>(commuterTexture, pos, commuterSize, sf::Vector2f(velocityX, 0));
    } else {
        return std::make_unique<Animal>(commuterTexture, pos, commuterSize, sf::Vector2f(velocityX, 0));
    }
}


void Lane::updateCurrent(sf::Time dt) {
    auto isLastCommuterFarEnough = [&]() {
        if (!commuters.empty()) {
            auto startX = velocityX > 0 ? 0 : WINDOW_VIDEO_MODE.width;
            auto &last = commuters.back();
            return std::abs((float) startX - last->getPosition().x) >= MINIMUM_WIDTH_BETWEEN_VEHICLES;
        } else
            return true;
    };

    timer -= dt;
    if (timer <= sf::Time::Zero && isLastCommuterFarEnough()) {
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
    auto sprite = TextureHolder::instance().getSpriteSheet(laneTexture).getSprite(0);
    // Set scale to match the height of the road
    auto scaleFactor = height / (float) sprite.getGlobalBounds().height;
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);

    for (float i = 0; i < (float) WINDOW_VIDEO_MODE.width;
         i += sprite.getLocalBounds().width) {
        sprite.setPosition(i, 0);
        target.draw(sprite, states);
    }
}

void Lane::onLightChanged() {
    if (type == Type::Vehicle) {
        for (auto &vehicle: commuters) {
            dynamic_cast<Vehicle *>(vehicle)->onLightChanged();
        }
    }
}

void Lane::setPosY(float y) {
    setPosition(0, y);
}

void Lane::setCommuterTexture(Texture::ID id) {
    commuterTexture = id;
}

void Lane::setLaneTexture(Texture::ID id) {
    laneTexture = id;
}

void Lane::setLaneHeight(float newHeight) {
    height = newHeight;
}

void Lane::setCommuterSize(sf::Vector2f size) {
    commuterSize = size;
}

void Lane::setDirection(Lane::Direction direction) {
    if (direction == Direction::Right) {
        velocityX = std::abs(velocityX);
    } else {
        velocityX = -std::abs(velocityX);
    }
}

void Lane::setSpeed(float speed) {
    velocityX /= std::abs(velocityX);
    velocityX *= speed;
}

void Lane::setFrequency(const Random<std::normal_distribution<double>> &newFrequency) {
    frequency = newFrequency;
}