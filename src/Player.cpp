#include "Player.h"
#include "Consts.h"
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

void Player::updateCurrent(sf::Time dt) {
    if (animation.isFinished()) {
        onJumpAnimationFinished();
    }

    switch (state) {
    case Idle:
        break;
    case Jumping:
        updateJump(dt);
        break;
    case Colliding:
        updateCollision(dt);
        break;
    }

    Entity::updateCurrent(dt);
}

Player::Player() : jumpTexture(Texture::ID::PlayerJumpUp), idleTexture(Texture::ID::PlayerIdleUp) {
    staticPos = getPosition();
    animation = AnimationMachine(idleTexture, sf::seconds(5), true);
}

Player::Player(sf::Vector2f position, sf::Vector2f size)
        : Entity(Texture::ID::PlayerIdleUp, position, size, DEF_PLAYER_VELOCITY),
          jumpTexture(Texture::ID::PlayerJumpUp),
          idleTexture(Texture::ID::PlayerIdleUp) {
    staticPos = getPosition();
    setVelocity({0, 0});
    adjustBounds(20, 20, 40, 40);
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    if (state != Idle) {
        return;
    }
    auto newPos = staticPos;
    if (state == Idle) {
        preJumpPos = getPosition();
        switch (event.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                newPos = {staticPos.x, staticPos.y - GRID_SIZE.y};
                jumpTexture = Texture::ID::PlayerJumpUp;
                idleTexture = Texture::ID::PlayerIdleUp;
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                newPos = {staticPos.x, staticPos.y + GRID_SIZE.y};
                jumpTexture = Texture::ID::PlayerJumpDown;
                idleTexture = Texture::ID::PlayerIdleDown;
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                newPos = {staticPos.x - GRID_SIZE.x, staticPos.y};
                jumpTexture = Texture::ID::PlayerJumpLeft;
                idleTexture = Texture::ID::PlayerIdleLeft;
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                newPos = {staticPos.x + GRID_SIZE.x, staticPos.y};
                jumpTexture = Texture::ID::PlayerJumpRight;
                idleTexture = Texture::ID::PlayerIdleRight;
                break;
            default:

                break;
        }
        animation = AnimationMachine(jumpTexture, JUMP_DURATION, false);
        staticPos = newPos;
        timeJumped = sf::Time::Zero;
        state = Jumping;
    }
}

bool Player::isJumping() const { return timeJumped < JUMP_DURATION; }

void Player::updateJump(sf::Time dt) {
    auto length = staticPos - getPosition();
    if (isJumping()) {
        auto timeLeft = JUMP_DURATION - timeJumped;
        setVelocity({length.x / timeLeft.asSeconds(), length.y / timeLeft.asSeconds()});
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale = -2 * ((timeJumped.asSeconds() / JUMP_DURATION.asSeconds()) - 1);
        setVelocity(getVelocity() * scale);
        timeJumped += dt;
    } else {
        setPosition(staticPos);
        setVelocity({0, 0});
        state = Idle;
    }
}

void Player::onJumpAnimationFinished() {
    animation = AnimationMachine(idleTexture, DEF_ANIMATION_DURATION, true);
}

void Player::onCollision(Entity *other) {
    if (state == Idle) {
        return;
    }
    if (state == Jumping) {
        state = Colliding;
        collisionTime = sf::Time::Zero;
        setVelocity({0, 0});
        staticPos = preJumpPos;
    }
}

void Player::updateCollision(sf::Time dt) {
    auto dist = staticPos - getPosition();
    if (collisionTime < sf::seconds(0.3)) {
        auto timeLeft = JUMP_DURATION - collisionTime;
        setVelocity({dist.x / timeLeft.asSeconds(), dist.y / timeLeft.asSeconds()});
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale = -2 * ((timeJumped.asSeconds() / JUMP_DURATION.asSeconds()) - 1);
        setVelocity(getVelocity() * scale);
        collisionTime += dt;
    } else {
        setPosition(preJumpPos);
        setVelocity({0, 0});
        state = Idle;
    }
}
