#pragma once

#include "Random.h"
#include "Lane.h"
#include "Entity.h"
#include "Commuters.h"
#include "Light.h"

#include <deque>
#include <functional>

class RoadLane : public Lane {
public:
    enum class Type {
        Vehicle, Animal, River
    };
    enum class Direction {
        Left = 0, Right = 1
    };

protected:
    float speedX;
    Direction direction;
    /**
     * Normal distribution. Determines when will another commuter appear.<br>
     * Mean is the average time between two commuters.<br>
     * Higher mean for higher difficulty. Lower mean for higher speed.
     */
    Random<std::normal_distribution<double>> frequency;
    sf::Time timer;
    Texture::ID laneTexture;
    float height;
    Texture::ID commuterTexture;
    sf::Vector2f commuterSize;
    std::deque<Entity *> commuters;

    virtual std::unique_ptr<Entity> newCommuter() const = 0;

    virtual void updateCommuters(sf::Time dt);

    sf::Vector2f getVelocity() const;

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

public:
    RoadLane();

    RoadLane(Texture::ID commuterTexture, Texture::ID laneTexture, float y, float speed,
             Random<std::normal_distribution<double>> frequency);

    RoadLane(Texture::ID commuterTexture, Texture::ID laneTexture, float y, float laneHeight,
             sf::Vector2f commuterSize, Direction direction, float speed,
             Random<std::normal_distribution<double>> frequency);

    virtual Type getType() const = 0;

    Direction getDirection() const;

    sf::FloatRect getLocalBounds() const override;

    void setPosY(float) override;

    void setLaneHeight(float) override;

    void setCommuterTexture(Texture::ID);

    void setLaneTexture(Texture::ID);

    void setCommuterSize(sf::Vector2f);

    void setDirection(Direction);

    void setSpeed(float);

    void setFrequency(Random<std::normal_distribution<double>> const &);
};

class VehicleLane : public RoadLane, public LightObserver {
public:
    using RoadLane::RoadLane;

    Type getType() const override;

    void onLightChanged() override;

protected:
    void updateCommuters(sf::Time dt) override;

private:
    bool stopSpawning = false;

    std::unique_ptr<Entity> newCommuter() const override;
};

class AnimalLane : public RoadLane {
public:
    using RoadLane::RoadLane;

    Type getType() const override;

private:
    std::unique_ptr<Entity> newCommuter() const override;
};

class WoodLane : public virtual RoadLane, public virtual PlayerCollidable {
public:
    WoodLane();

    WoodLane(Texture::ID waterBeforeWoodTexture, Texture::ID waterTexture, Texture::ID waterAfterWoodTexture, Texture::ID woodTexture, float y, float speed,
            Random<std::normal_distribution<double>> frequency);

    WoodLane(Texture::ID waterBeforeWoodTexture, Texture::ID waterTexture, Texture::ID waterAfterWoodTexture, Texture::ID woodTexture, float y, float laneHeight,
            float minWaterWidth, float maxWaterWidth, Direction direction, float speed,
            Random<std::normal_distribution<double>> frequency);

    Type getType() const override;

    Category::Type getCategory() const override;

    void setMaxWaterWidth(float width);

    void spawnWaterInMiddle();

private:
    float maxWaterWidth;
    Texture::ID waterBeforeWoodTexture, waterAfterWoodTexture;

    void updateCurrent(sf::Time dt) override;

    void onStartPlayerCollision() override;

    void onEndPlayerCollision() override;

    std::unique_ptr<Entity> newCommuter() const override;
};