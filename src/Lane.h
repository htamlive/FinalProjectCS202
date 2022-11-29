#pragma once

#include "SceneNode.h"
#include "Random.h"
#include "Entity.h"

#include <deque>

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
    Direction direction;
    float speed;
    std::deque<Entity *> commuters;

    /**
     * Normal distribution. Determines when will another commuter appear.<br>
     * Mean is the average time between two commuters.<br>
     * Higher mean for higher difficulty. Lower mean for higher speed.
     */
    Random frequency;
    sf::Time timer;

    float height;
    sf::Vector2f commuterSize;
    Texture::ID commuterTexture;
    Texture::ID laneTexture;

    std::unique_ptr<Entity> newCommuter() const;

public:
    Lane();

    Lane(Type type, Texture::ID commuterTexture, Texture::ID laneTexture, float x, float y, float roadHeight,
         float commuterWidth, float commuterHeight, Direction direction, float speed, Random frequency);

    void updateCurrent(sf::Time dt) override;

    void drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const override;

    void onLightChanged();

    sf::Vector2f getVelocity() const;
};