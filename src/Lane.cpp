#include "Lane.h"
#include "Vehicle.h"
#include "Animal.h"

Lane::Lane() : type(Type::Vehicle), commuterTexture(), laneTexture(), height(0), commuterSize(),
               direction(Direction::Right), speed(0), frequency() {}

Lane::Lane(Lane::Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float height,
           float commuterWidth, float commuterHeight, Lane::Direction direction, float speed, Random frequency) : type(type),
                                                                                                                  commuterTexture(commuterTexture),
                                                                                                                  laneTexture(laneTexture),
                                                                                                                  height(height),
                                                                                                                  commuterSize({commuterWidth,
                                                                                                                                commuterHeight}),
                                                                                                                  direction(direction),
                                                                                                                  speed(speed),
                                                                                                                  frequency(frequency) {
    setPosition(0, y);
}

void Lane::updateCurrent(sf::Time dt) {
    timer -= dt;
    if (timer <= sf::Time::Zero) {
        // Add a new vehicle
        auto commuter = newCommuter();
        commuters.push_back(commuter.get());
        attachChild(std::move(commuter));
        timer = sf::seconds(frequency.get<float>());
    }

    // Remove vehicles out of screen
    while (!commuters.empty() && commuters.front()->isOutOfScreen()) {
        detachChild(*commuters.front());
        commuters.pop_front();
    }
}

void Lane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    sf::Sprite sprite(TextureHolder::instance().get(laneTexture).texture);
    // Set scale to match the height of the road
    auto scaleFactor = height / (float) sprite.getTexture()->getSize().y;
    sprite.setScale(scaleFactor, scaleFactor);

    for (float i = 0; i < (float) WINDOW_VIDEO_MODE.width; i += sprite.getLocalBounds().width) {
        sprite.setPosition(i, getPosition().y);
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

sf::Vector2f Lane::getVelocity() const {
    if (direction == Direction::Right) {
        return {speed, 0};
    } else {
        return {-speed, 0};
    }
}

std::unique_ptr<Entity> Lane::newCommuter() const {
    auto pos = direction == Direction::Right ? sf::Vector2f(-commuterSize.x + 1, getPosition().y) : sf::Vector2f(
            (float) WINDOW_VIDEO_MODE.width - 1, getPosition().y);
    if (type == Type::Vehicle) {
        return std::make_unique<Vehicle>(getVelocity(), pos.x, pos.y,
                                         commuterSize.x, commuterSize.y, commuterTexture);
    } else {
        return std::make_unique<Animal>(getVelocity(), pos.x, pos.y,
                                        commuterSize.x, commuterSize.y, commuterTexture);
    }
}
