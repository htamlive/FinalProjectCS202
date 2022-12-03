#include "Player.h"
#include "AudioController.h"
#include "Consts.h"
#include "TextureHolder.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

void Player::updateCurrent(sf::Time dt) {
    if (animation.isFinished()) {
        onJumpAnimationFinished();
    }

    calVelocity(dt);

    Entity::updateCurrent(dt);
}

Player::Player() : jumpTexture(Texture::ID::PlayerJumpUp), idleTexture(Texture::ID::PlayerIdleUp) {
    staticPos = getPosition();
    animation = AnimationMachine(idleTexture, sf::seconds(5), true);
}

Player::Player(float x, float y, float w, float h)
        : Entity({100, 100}, x, y, w, h, Texture::ID::PlayerIdleUp),
          jumpTexture(Texture::ID::PlayerJumpUp),
          idleTexture(Texture::ID::PlayerIdleUp) {
    staticPos = getPosition();
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    auto newPos = staticPos;
    if (!isJumping()) {
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
    }

    if (staticPos != newPos) {
        animation = AnimationMachine(jumpTexture, JUMP_DURATION, false);
        staticPos = newPos;
        timeJumped = sf::Time::Zero;
    }
}

bool Player::isJumping() const { return timeJumped < JUMP_DURATION; }

void Player::calVelocity(sf::Time dt) {
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
        setVelocity({length.x / dt.asSeconds(), length.y / dt.asSeconds()});
    }
}

void Player::onJumpAnimationFinished() {
    animation = AnimationMachine(idleTexture, DEF_ANIMATION_DURATION, true);
}
