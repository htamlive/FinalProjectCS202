#include "PlayerState.h"
#include "Player.h"

PlayerState::PlayerState(Player *player) : player(player) {}
PlayerState::~PlayerState() = default;

JumpingState::JumpingState(Player *player)
    : PlayerState(player) {
    player->animation =
        AnimationMachine(player->jumpTexture, JUMP_DURATION, false);
}

void JumpingState::update(sf::Time dt) {
    auto p = player;
    auto length = p->staticPos - p->getPosition();
    if (isJumping()) {
        auto timeLeft = jumpDuration - jumpTime;
        sf::Vector2f vel = {length.x / timeLeft.asSeconds(),
                            length.y / timeLeft.asSeconds()};
        if (p->onSpeedBoost) {
            vel = {vel.x * 2, vel.y * 2};
        }
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
            -2 * ((jumpTime.asSeconds() / jumpDuration.asSeconds()) - 1);
        p->setVelocity(vel * scale);
        jumpTime += dt;
        return;
    }
    p->setPosition(p->staticPos);
    p->setVelocity({0, 0});
    p->setState(new IdleState(p));
    p->animation =
        AnimationMachine(p->idleTexture, DEF_ANIMATION_DURATION, true);
}

void CollidingState::update(sf::Time dt) {
    auto playerPos = player->getPosition();
    auto dist = player->preJumpPos - playerPos;
    if (collisionTime < sf::seconds(0.3)) {
        auto timeLeft = JUMP_DURATION - collisionTime;
        sf::Vector2f vel = {dist.x / timeLeft.asSeconds(),
                            dist.y / timeLeft.asSeconds()};
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
            -2 * ((collisionTime.asSeconds() / JUMP_DURATION.asSeconds()) - 1);
        player->setVelocity(vel * scale);
        collisionTime += dt;
    } else {
        player->setPosition(player->preJumpPos);
        player->setVelocity({0, 0});
        player->setState(new IdleState(player));
    }
}

void IdleState::update(sf::Time dt) {}
void SpeedBoostingState::update(sf::Time dt) {}

void SmallSizeBoostingState::update(sf::Time dt) {
    auto p = player;
    if (p->animation.isFinished()) {
        p->setState(new IdleState(p));
        p->animation =
            AnimationMachine(p->idleTexture, DEF_ANIMATION_DURATION, true);
    }
}
