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

protected:
    void updateCurrent(sf::Time dt) override;

private:
    bool isJumping() const;

    void calVelocity(sf::Time dt);

    void onJumpAnimationFinished();

    sf::Vector2f staticPos;

    sf::Time timeJumped;

    Texture::ID jumpTexture, idleTexture;
};