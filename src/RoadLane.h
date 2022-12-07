#pragma once

#include "Random.h"
#include "Entity.h"
#include "Lane.h"

#include <deque>

#include <functional>

class RoadLane : public Lane {
public:
    enum class Type {
        Vehicle, Animal
    };
    enum class Direction {
        Left = 0, Right = 1
    };

private:
    Type type;
    float velocityX;
    std::deque<Entity *> commuters;

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

    std::unique_ptr<Entity> newCommuter() const;

public:
    RoadLane();

    RoadLane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float speed, Random<std::normal_distribution<double>> frequency);

    RoadLane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float laneHeight,
             float commuterWidth, float commuterHeight, Direction direction, float speed,
             Random<std::normal_distribution<double>> frequency);

    float getTopY() const override;

    float getBottomY() const override;

    void setPosY(float) override;

    void setLaneHeight(float) override;

    void setCommuterTexture(Texture::ID);

    void setLaneTexture(Texture::ID);

    void setCommuterSize(sf::Vector2f);

    void setDirection(Direction);

    void setSpeed(float);

    void setFrequency(Random<std::normal_distribution<double>> const &);

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onLightChanged();
};
