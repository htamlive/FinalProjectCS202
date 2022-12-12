#pragma once

#include "Entity.h"

enum PlayerState {
    Idle,
    Jumping,
    Colliding
};

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
    void onCollision(Entity *other);
    Category getCategory() const override;

private:
    void updateCurrent(sf::Time dt) override;

    bool isJumping() const;

    void updateJump(sf::Time dt);

    void onJumpAnimationFinished();

    void updateCollision(sf::Time dt);

    sf::Vector2f staticPos;

    sf::Time timeJumped;

    Texture::ID jumpTexture, idleTexture;
    
    sf::Time collisionTime;
    sf::Vector2f preJumpPos;
    PlayerState state = Idle;
};
