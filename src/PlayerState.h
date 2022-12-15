#include <SFML/Graphics.hpp>
#include <iostream>
#include "Consts.h"
#include "Player.h"

class PlayerState {
public:
    PlayerState(Player *);
    virtual ~PlayerState();
    virtual void update(sf::Time dt) = 0;
    Player *player;
};

class JumpingState : public PlayerState {
    sf::Time jumpTime = sf::Time::Zero;
    sf::Time jumpDuration = JUMP_DURATION;
    bool onBoost;
public:
    JumpingState(Player *player);
    bool isJumping() const { return jumpTime < jumpDuration; }
    void update(sf::Time dt) override;
};

class IdleState : public PlayerState {
public:
    using PlayerState::PlayerState;
    void update(sf::Time dt) override;
};

class SmallSizeBoostingState : public PlayerState {
    sf::Time boostTime = sf::Time::Zero;
public:
    SmallSizeBoostingState(Player *player);
    void update(sf::Time dt) override;
};

class SpeedBoostingState : public PlayerState {
public:
    using PlayerState::PlayerState;
    void update(sf::Time dt) override;
};

class CollidingState : public PlayerState {
    sf::Time collisionTime = sf::Time::Zero;
public:
    using PlayerState::PlayerState;
    void update(sf::Time dt) override;
};
