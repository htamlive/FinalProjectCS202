#pragma once

#include "Entity.h"

/**
 * Note: character jumps only once each press. That allows user to control the speed (by pressing faster or slower).
 */
class Player : public Entity {
public:
    Player();

    Player(float x, float y, float w, float h);

    void onKeyPressed(sf::Event::KeyEvent);

private:
    void drawCurrent(sf::RenderTarget &target, sf::RenderStates state) const override;

    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    void calVelocity(sf::Time dt);

    void onJumpAnimationFinished();

    void jump(sf::Vector2f dest);

    sf::Vector2f destination;

    sf::Time time_jumped;
};