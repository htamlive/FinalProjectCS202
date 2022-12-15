#include "PlayerState.h"
#include "Consts.h"
#include "Player.h"
#include <SFML/System/Time.hpp>

PlayerState::PlayerState(Player *player) : player(player) {}
PlayerState::~PlayerState() = default;

JumpingState::JumpingState(Player *player, sf::Vector2f jumpPos)
    : PlayerState(player), jumpPos(jumpPos) {
    player->animation =
        AnimationMachine(player->jumpTexture, JUMP_DURATION, false);
}

void JumpingState::update(sf::Time dt) {
    auto p = player;
    auto length = jumpPos - p->getPosition();
    if (isJumping()) {
        auto timeLeft = jumpDuration - jumpTime;
        sf::Vector2f vel = {length.x / timeLeft.asSeconds(),
                            length.y / timeLeft.asSeconds()};
        if (p->onSpeedBoost) {
            vel = vel * 2.f;
        }
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
            -2 * ((jumpTime.asSeconds() / jumpDuration.asSeconds()) - 1);
        p->setVelocity(vel * scale);
        jumpTime += dt;
        return;
    }
    p->setPosition(jumpPos);
    p->setVelocity({0, 0});
    p->setState(new IdleState(p));
}

CollidingState::CollidingState(Player *player, sf::Vector2f collisionPos)
    : PlayerState(player), collisionPos(collisionPos) {
    player->animation =
        AnimationMachine(player->jumpTexture, sf::seconds(0.8), false);
    player->isInvincible = true;
}

void CollidingState::update(sf::Time dt) {
    auto playerPos = player->getPosition();
    auto dist = collisionPos - playerPos;
    if (collisionTime < collisionDuration) {
        auto timeLeft = collisionDuration - collisionTime;
        sf::Vector2f vel = {dist.x / timeLeft.asSeconds(),
                            dist.y / timeLeft.asSeconds()};
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
            -2 * ((collisionTime.asSeconds() / collisionDuration.asSeconds()) - 1);
        player->setVelocity(vel * scale);
        collisionTime += dt;
    } else {
        player->setPosition(collisionPos);
        player->setVelocity({0, 0});
        player->setState(new IdleState(player));
    }
}

void IdleState::update(sf::Time dt) {}

StunnedState::StunnedState(Player *player) : PlayerState(player) {
    player->animation =
        AnimationMachine(player->idleTexture, DEF_ANIMATION_DURATION, false);
}

void StunnedState::update(sf::Time dt) {
    stunTime += dt;
    if (stunTime > stunDuration) {
        player->setState(new IdleState(player));
    }
}

ObstacleCollidingState::ObstacleCollidingState(Player *player,
                                               sf::Vector2f collisionPos)
    : PlayerState(player), collisionPos(collisionPos) {
    player->animation =
        AnimationMachine(player->jumpTexture, sf::seconds(0.8), false);
}

void ObstacleCollidingState::update(sf::Time dt) {
    auto playerPos = player->getPosition();
    auto dist = collisionPos - playerPos;
    if (collisionTime < collisionDuration) {
        auto timeLeft = collisionDuration - collisionTime;
        sf::Vector2f vel = {dist.x / timeLeft.asSeconds(),
                            dist.y / timeLeft.asSeconds()};
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
            -2 * ((collisionTime.asSeconds() / collisionDuration.asSeconds()) - 1);
        player->setVelocity(vel * scale);
        collisionTime += dt;
    } else {
        player->setPosition(collisionPos);
        player->setVelocity({0, 0});
        player->setState(new StunnedState(player));
    }
}

InvincibleState::InvincibleState(Player *player) : PlayerState(player) {
    std::cout << "Invincible" << std::endl;
    player->animation =
        AnimationMachine(player->idleTexture, DEF_ANIMATION_DURATION, false);
    savedBounds = player->localBounds;
}

void InvincibleState::update(sf::Time dt) {
    invincibleTime += dt;
    if (invincibleTime > invincibleDuration) {
        player->localBounds = savedBounds;
        player->setState(new IdleState(player));
    }
}

DyingState::DyingState(Player *player) : PlayerState(player) {
    player->animation =
        AnimationMachine(player->idleTexture, DEF_ANIMATION_DURATION, false);
    player->setVelocity({0, 0});
    player->localBounds = sf::FloatRect(0, 0, 0, 0);
}

void DyingState::update(sf::Time dt) {
    dyingTime += dt;
    if (dyingTime > dyingDuration) {
        player->setState(new DeadState(player));
    }
}

DeadState::DeadState(Player *player) : PlayerState(player) {
    player->animation =
        AnimationMachine(player->idleTexture, DEF_ANIMATION_DURATION, false);
    player->setVelocity({0, 0});
    player->localBounds = sf::FloatRect(0, 0, 0, 0);
}

void DeadState::update(sf::Time dt) {}
