#include "RoadLane.h"
#include "Commuters.h"
#include <iostream>

static const float OFFSET_FROM_PAVEMENT = 15;

RoadLane::RoadLane()
        : speedX(0), height(0),
          frequency(), laneTexture(), commuterTexture(), commuterSize(0, 0), direction(Direction::Left) {
    setPosition(0, 0);
}

RoadLane::RoadLane(Texture::ID commuterTexture, Texture::ID laneTexture, float y, float speed,
                   Random<std::normal_distribution<double>> frequency) : laneTexture(laneTexture), frequency(frequency),
                                                                         speedX(speed), height(DEF_LANE_HEIGHT),
                                                                         commuterTexture(commuterTexture),
                                                                         commuterSize(DEF_COMMUTER_SIZE),
                                                                         direction(Direction::Left) {
    setPosition(0, y);
}

RoadLane::RoadLane(Texture::ID commuterTexture,
                   Texture::ID laneTexture, float y, float laneHeight,
                   sf::Vector2f commuterSize, RoadLane::Direction direction,
                   float speed, Random<std::normal_distribution<double>> frequency)
        : laneTexture(laneTexture),
          frequency(frequency), height(laneHeight), commuterTexture(commuterTexture),
          commuterSize(commuterSize), direction(direction), speedX(speed) {
    setPosition(0, y);
}

void RoadLane::updateCommuters(sf::Time dt) {
    auto isLastCommuterFarEnough = [&]() {
        if (!commuters.empty()) {
            if (getDirection() == Direction::Right) {
                auto startX = getLocalBounds().left;
                auto &last = commuters.back();
                return last->getPosition().x - startX >= MINIMUM_WIDTH_BETWEEN_VEHICLES;
            } else {
                auto startX = getLocalBounds().left + getLocalBounds().width;
                auto &last = commuters.back();
                return startX - last->getPosition().x - last->getSpriteBounds().width >= MINIMUM_WIDTH_BETWEEN_VEHICLES;

            }
        } else
            return true;
    };

    auto isOutOfScreen = [&](Entity const &commuter) {
        if (getDirection() == Direction::Right) {
            return commuter.getPosition().x > (float) DESTROY_BORDER.width;
        } else {
            return commuter.getPosition().x + commuter.getSpriteBounds().width < DESTROY_BORDER.left;
        }
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
    while (!commuters.empty() && isOutOfScreen(*commuters.front())) {
        std::cout << "Remove commuter" << std::endl;
        detachChild(*commuters.front());
        commuters.pop_front();
    }
}

void RoadLane::updateCurrent(sf::Time dt) {
    updateCommuters(dt);
}

void RoadLane::setLaneTexture(Texture::ID texture) {
    laneTexture = texture;
}

void RoadLane::setCommuterTexture(Texture::ID id) {
    commuterTexture = id;
}

void RoadLane::setCommuterSize(sf::Vector2f size) {
    commuterSize = size;
}

void RoadLane::setDirection(RoadLane::Direction newDirection) {
    direction = newDirection;
}

void RoadLane::setSpeed(float speed) {
    speedX = speed;
}

sf::FloatRect RoadLane::getLocalBounds() const {
    return {0, 0, (float) WINDOW_VIDEO_MODE.width, height};
}

void RoadLane::setFrequency(const Random<std::normal_distribution<double>> &newFrequency) {
    frequency = newFrequency;
}

void RoadLane::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const {
    auto sprite = TextureHolder::instance().getSheet(laneTexture).getSprite(0);
    // Set scale to match the height of the road
    auto scaleFactor = height / (float) sprite.getGlobalBounds().height;
    sprite.setScale(sprite.getScale().x * scaleFactor, sprite.getScale().y * scaleFactor);

    for (float i = 0; i < (float) WINDOW_VIDEO_MODE.width; i += sprite.getGlobalBounds().width) {
        sprite.setPosition(i, 0);
        target.draw(sprite, states);
    }
}

void RoadLane::setPosY(float y) {
    setPosition(0, y);
}

void RoadLane::setLaneHeight(float newHeight) {
    height = newHeight;
}

RoadLane::Direction RoadLane::getDirection() const {
    return direction;
}

sf::Vector2f RoadLane::getVelocity() const {
    if (direction == Direction::Right)
        return {speedX, 0};
    else
        return {-speedX, 0};
}

RoadLane::Type VehicleLane::getType() const {
    return RoadLane::Type::Vehicle;
}

void VehicleLane::onLightChanged() {
    stopSpawning = !stopSpawning;
    for (auto &commuter: commuters)
        dynamic_cast<Vehicle *>(commuter)->onLightChanged();
}

std::unique_ptr<Entity> VehicleLane::newCommuter() const {
    auto pos =
            getDirection() == Direction::Right
            ? sf::Vector2f(-commuterSize.x + 1, 0)
            : sf::Vector2f((float) WINDOW_VIDEO_MODE.width - 1, 0);
    auto vehicle = std::make_unique<Vehicle>(commuterTexture, pos, commuterSize, getVelocity());
    vehicle->adjustBounds(0, 0, 0, 40);
    vehicle->adjustSpriteBounds(0, height - commuterSize.y - OFFSET_FROM_PAVEMENT);
    return vehicle;
}

void VehicleLane::updateCommuters(sf::Time dt) {
    if (!stopSpawning)
        RoadLane::updateCommuters(dt);
}

RoadLane::Type AnimalLane::getType() const {
    return RoadLane::Type::Animal;
}

std::unique_ptr<Entity> AnimalLane::newCommuter() const {
    auto pos =
            getDirection() == Direction::Right
            ? sf::Vector2f(-commuterSize.x + 1, 0)
            : sf::Vector2f((float) WINDOW_VIDEO_MODE.width - 1, 0);
    auto animal = std::make_unique<Animal>(commuterTexture, pos, commuterSize, getVelocity());


    if (commuterTexture == Texture::ID::RightCucumber || commuterTexture == Texture::ID::LeftCucumber) {
        animal->adjustBounds(30, 0, 60, 40);
    } else if (commuterTexture == Texture::RightPlane || commuterTexture == Texture::LeftPlane) {
        animal->adjustBounds(0, 0, 0, 40);
    }
    animal->adjustSpriteBounds(0, height - commuterSize.y - OFFSET_FROM_PAVEMENT);
    return animal;
}

WoodLane::WoodLane() : RoadLane(), maxWaterWidth(0) {}

WoodLane::WoodLane(Texture::ID waterBeforeWoodTexture, Texture::ID waterTexture, Texture::ID waterAfterWoodTexture,
                   Texture::ID woodTexture, float y, float speed,
                   Random<std::normal_distribution<double>> frequency) : RoadLane(waterTexture, woodTexture, y,
                                                                                  speed, frequency),
                                                                         waterBeforeWoodTexture(waterBeforeWoodTexture),
                                                                         waterAfterWoodTexture(waterAfterWoodTexture) {
    maxWaterWidth = commuterSize.x;
}

WoodLane::WoodLane(Texture::ID waterBeforeWoodTexture, Texture::ID waterTexture, Texture::ID waterAfterWoodTexture,
                   Texture::ID woodTexture, float y, float laneHeight, float minWaterWidth,
                   float maxWaterWidth, RoadLane::Direction direction, float speed,
                   Random<std::normal_distribution<double>> frequency) : RoadLane(waterTexture, woodTexture, y,
                                                                                  laneHeight,
                                                                                  {laneHeight, minWaterWidth},
                                                                                  direction, speed, frequency),
                                                                         waterBeforeWoodTexture(waterBeforeWoodTexture),
                                                                         waterAfterWoodTexture(waterAfterWoodTexture) {
    this->maxWaterWidth = std::max(maxWaterWidth, commuterSize.x);
}

RoadLane::Type WoodLane::getType() const {
    return RoadLane::Type::River;
}

std::unique_ptr<Entity> WoodLane::newCommuter() const {
    sf::Vector2f squareSize = {height, height};
    auto width = Random(std::uniform_real_distribution<>(commuterSize.x, maxWaterWidth)).get<float>();
    auto pos =
            getDirection() == Direction::Right
            ? sf::Vector2f(-width + 1, 0)
            : sf::Vector2f((float) WINDOW_VIDEO_MODE.width - 1, 0);
    auto water = std::make_unique<Water>(waterAfterWoodTexture, commuterTexture, waterBeforeWoodTexture, pos,
                                         squareSize, width / squareSize.x, getVelocity());
    return water;
}

Category::Type WoodLane::getCategory() const {
    return Category::Type::Wood;
}

void WoodLane::onStartPlayerCollision() {
    player->addPlatformVelocity(getVelocity());
}

void WoodLane::onEndPlayerCollision() {
    player->addPlatformVelocity(-getVelocity());
}

void WoodLane::updateCurrent(sf::Time dt) {
    RoadLane::updateCurrent(dt);
    PlayerCollidable::updateCurrent(dt);
}

void WoodLane::setMaxWaterWidth(float width) {
    this->maxWaterWidth = std::max(width, commuterSize.x);
}

void WoodLane::spawnWaterInMiddle() {
    auto rand = Random(std::uniform_real_distribution<>(0, getLocalBounds().width));

    for (float x = 0; x < getLocalBounds().width; x += MINIMUM_WIDTH_BETWEEN_VEHICLES) {
        x = rand.get<float>(x, getLocalBounds().width);
        auto water = newCommuter();
        water->setPosition(x, 0);
        x += water->getSpriteBounds().width;

        commuters.push_back(water.get());
        attachChild(std::move(water));
    }
}