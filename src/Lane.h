#pragma once

#include "SceneNode.h"
#include "Random.h"
#include "Entity.h"

#include <deque>

#include <functional>

class Lane : public SceneNode {
public:
    enum class Direction {
        Left = 0, Right = 1
    };
    enum class Type {
        Vehicle, Animal
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
    float height;
    Texture::ID laneTexture;

    Texture::ID commuterTexture;
    sf::Vector2f commuterSize;

    std::unique_ptr<Entity> newCommuter() const;

public:
    Lane();

    Lane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float speed, Random<std::normal_distribution<double>> frequency);

    Lane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float laneHeight,
         float commuterWidth, float commuterHeight, Direction direction, float speed,
         Random<std::normal_distribution<double>> frequency);

    void setPosY(float);

    void setCommuterTexture(Texture::ID);

    void setLaneTexture(Texture::ID);

    void setLaneHeight(float);

    void setCommuterSize(sf::Vector2f);

    void setDirection(Direction);

    void setSpeed(float);

    void setFrequency(Random<std::normal_distribution<double>> const &);

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onLightChanged();
};
