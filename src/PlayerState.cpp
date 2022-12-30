#include "PlayerState.h"
#include "Consts.h"
#include "Player.h"
#include <SFML/System/Time.hpp>
#include "AudioController.h"

PlayerState::PlayerState(Player *player) : player(player) {}

PlayerState::~PlayerState() = default;

JumpingState::JumpingState(Player *player, sf::Vector2f jumpPos)
        : PlayerState(player), jumpPos(jumpPos) {
    player->animation =
            AnimationMachine(player->getJumpTexture(), JUMP_DURATION, false);
    AudioController::instance().playSound(SoundEffect::Jump);
}

void JumpingState::update(sf::Time dt) {
    auto p = player;
    auto length = jumpPos - p->getPosition();
    if (isJumping()) {
        auto curJumpDuration = jumpDuration * player->jumpDurationScale;
        auto timeLeft = curJumpDuration - jumpTime;
        sf::Vector2f vel = {length.x / timeLeft.asSeconds(),
                            length.y / timeLeft.asSeconds()};

        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale =
                -2 * ((jumpTime.asSeconds() / curJumpDuration.asSeconds()) - 1);
        p->setVelocity(vel * scale);
        jumpTime += dt;
    } else {
        p->setPosition(jumpPos);
        p->setVelocity({0, 0});
        p->setState(new IdleState(p));
    }
}

CollidingState::CollidingState(Player *player, sf::Vector2f collisionPos, sf::Time collisionDuration) : PlayerState(
        player), collisionPos(collisionPos), collisionDuration(collisionDuration) {
    player->animation =
            AnimationMachine(player->getJumpTexture(), collisionDuration, false);
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
                -2 *
                ((collisionTime.asSeconds() / collisionDuration.asSeconds()) - 1);
        player->setVelocity(vel * scale);
        collisionTime += dt;
    } else {
        player->setPosition(collisionPos);
        player->setVelocity({0, 0});
        player->setState(new IdleState(player));
    }
}

ObstacleCollidingState::ObstacleCollidingState(Player *player,
                                               sf::Vector2f collisionPos)
        : CollidingState(player, collisionPos, sf::seconds(0.3)) {}

void ObstacleCollidingState::update(sf::Time dt) {
    CollidingState::update(dt);
    if (collisionTime >= collisionDuration) {
        player->setState(new StunnedState(player));
    }
}

IdleState::IdleState(Player *player) : PlayerState(player) {
    player->animation =
            AnimationMachine(player->getIdleTexture(), DEF_ANIMATION_DURATION, true);
}

void IdleState::update(sf::Time dt) {
    if (player->getIdleTexture() != player->animation.getID()) {
        player->animation =
                AnimationMachine(player->getIdleTexture(), DEF_ANIMATION_DURATION, true);
    }
    player->setVelocity(player->platformVelocity);
}

StunnedState::StunnedState(Player *player) : PlayerState(player) {
    player->animation =
            AnimationMachine(player->getStunnedTexture(), DEF_ANIMATION_DURATION, false);
    AudioController::instance().playSound(SoundEffect::Stun);
}

void StunnedState::update(sf::Time dt) {
    stunTime += dt;
    player->setVelocity(player->platformVelocity);
    if (stunTime > stunDuration) {
        player->setState(new IdleState(player));
    }
}

InvincibleState::InvincibleState(Player *player) : PlayerState(player) {
    std::cout << "Invincible" << std::endl;
    player->animation =
            AnimationMachine(player->getIdleTexture(), DEF_ANIMATION_DURATION, false);
    savedBounds = player->localBounds;
}

void InvincibleState::update(sf::Time dt) {
    invincibleTime += dt;
    player->setVelocity(player->platformVelocity);
    if (invincibleTime > invincibleDuration) {
        player->localBounds = savedBounds;
        player->setState(new IdleState(player));
    }
}

DyingState::DyingState(Player *player) : PlayerState(player) {
    player->animation =
            AnimationMachine(player->getRipTexture(), sf::seconds(0.f), false);
    player->setVelocity({0, 0});
    player->localBounds = sf::FloatRect(0, 0, 0, 0);
    AudioController::instance().playSound(SoundEffect::GameOver);
}

void DyingState::update(sf::Time dt) {
    dyingTime += dt;
    if (dyingTime > dyingDuration) {
        player->setState(new DeadState(player));
    }
}

DeadState::DeadState(Player *player) : PlayerState(player) {
    player->animation =
            AnimationMachine(player->getRipTexture(), DEF_ANIMATION_DURATION, false);
    player->setVelocity({0, 0});
    player->localBounds = sf::FloatRect(0, 0, 0, 0);

    player->deadFlag = true;

}

void DeadState::update(sf::Time dt) {}
