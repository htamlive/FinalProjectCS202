#pragma once

#include "SceneNode.h"
#include "Random.h"
#include "Entity.h"

#include <deque>

#include <functional>

class Lane : public SceneNode {
public:
    enum class Direction {
        Right, Left
    };
    enum class Type {
        Vehicle, Animal
    };

private:
    Type type;
    sf::Vector2f velocity;
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

    std::function <std::unique_ptr<Entity>()> newCommuter;

public:
    Lane();

    Lane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float y, float laneHeight,
         float commuterWidth, float commuterHeight, Direction direction, float speed,
         Random<std::normal_distribution<double>> frequency);

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onLightChanged();
};
