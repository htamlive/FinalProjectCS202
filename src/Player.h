#pragma once

#include "Entity.h"

/**
 * @brief The Player class
 *
 * Note: character jumps only once each press. That allows user to control the speed (by pressing faster or slower).
 */
class Player : public Entity {
public:
    Player();

    Player(sf::Vector2f position, sf::Vector2f size);

    void onKeyPressed(sf::Event::KeyEvent);

private:
    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    void calVelocity(sf::Time dt);

    void onJumpAnimationFinished();

    sf::Vector2f staticPos;

    sf::Time timeJumped;

    Texture::ID jumpTexture, idleTexture;
};