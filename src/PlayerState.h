#pragma once

#include "Consts.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

class PlayerState {
public:
    enum StateID {
        Idle,
        Jumping,
        Dying,
        Colliding,
        Invincible,
        Stunned,
        Dead
    };
    PlayerState(Player *);
    virtual ~PlayerState();
    virtual void    update(sf::Time dt) = 0;
    virtual StateID getStateID() const  = 0;
    Player         *player;
};

class JumpingState : public PlayerState {
    sf::Time     jumpTime     = sf::Time::Zero;
    sf::Time     jumpDuration = JUMP_DURATION;
    sf::Vector2f jumpPos;

public:
    JumpingState(Player *player, sf::Vector2f jumpPos);
    bool    isJumping() const { return jumpTime < jumpDuration; }
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Jumping; }
};

class IdleState : public PlayerState {
public:
    IdleState(Player *player);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Idle; }
};

class CollidingState : public PlayerState {
protected:
    sf::Time      collisionTime = sf::Time::Zero;
    sf::Vector2f  collisionPos;
    sf::Time      collisionDuration;

public:
    CollidingState(Player *player, sf::Vector2f collisionPos, sf::Time collisionDuration = RECOIL_AFTER_COLLIDING_DURATION);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Colliding; }
};

class ObstacleCollidingState : public CollidingState {
public:
    ObstacleCollidingState(Player *player, sf::Vector2f collisionPos);
    void    update(sf::Time dt) override;
};

class StunnedState : public PlayerState {
    sf::Time stunTime     = sf::Time::Zero;
    sf::Time stunDuration = sf::seconds(0.5);

public:
    StunnedState(Player *player);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Stunned; }
};

class InvincibleState : public PlayerState {
    sf::Time      invincibleTime     = sf::Time::Zero;
    sf::Time      invincibleDuration = sf::seconds(1.5);
    sf::FloatRect savedBounds;

public:
    InvincibleState(Player *player);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Invincible; }
};

class DyingState : public PlayerState {
    sf::Time dyingTime     = sf::Time::Zero;
    sf::Time dyingDuration = sf::seconds(1.f);

public:
    DyingState(Player *player);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Dying; }
};

class DeadState : public PlayerState {
public:
    DeadState(Player *player);
    void    update(sf::Time dt) override;
    StateID getStateID() const override { return StateID::Dead; }
};