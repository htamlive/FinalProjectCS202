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

Player::Player() : jump_texture(Texture::ID::PlayerJumpUp), idle_texture(Texture::ID::PlayerIdleUp) {
    static_pos = getPosition();
    animation = AnimationMachine(idle_texture, sf::seconds(5), true);
}

Player::Player(float x, float y, float w, float h)
        : Entity({0, 0}, x, y, w, h, Texture::ID::PlayerIdleUp),
          jump_texture(Texture::ID::PlayerJumpUp),
          idle_texture(Texture::ID::PlayerIdleUp) {
    static_pos = getPosition();
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    auto new_pos = static_pos;
    if (!isJumping()) {
        switch (event.code) {
            case sf::Keyboard::W:
            case sf::Keyboard::Up:
                new_pos = {static_pos.x, static_pos.y - GRID_SIZE.y};
                jump_texture = Texture::ID::PlayerJumpUp;
                idle_texture = Texture::ID::PlayerIdleUp;
                break;
            case sf::Keyboard::S:
            case sf::Keyboard::Down:
                new_pos = {static_pos.x, static_pos.y + GRID_SIZE.y};
                jump_texture = Texture::ID::PlayerJumpDown;
                idle_texture = Texture::ID::PlayerIdleDown;
                break;
            case sf::Keyboard::A:
            case sf::Keyboard::Left:
                new_pos = {static_pos.x - GRID_SIZE.x, static_pos.y};
                jump_texture = Texture::ID::PlayerJumpLeft;
                idle_texture = Texture::ID::PlayerIdleLeft;
                break;
            case sf::Keyboard::D:
            case sf::Keyboard::Right:
                new_pos = {static_pos.x + GRID_SIZE.x, static_pos.y};
                jump_texture = Texture::ID::PlayerJumpRight;
                idle_texture = Texture::ID::PlayerIdleRight;
                break;
            default:
                
                break;
        }
    }

    if (static_pos != new_pos) {
        animation = AnimationMachine(jump_texture, JUMP_DURATION, false);
        static_pos = new_pos;
        time_jumped = sf::Time::Zero;
    }
}

bool Player::isJumping() const { return time_jumped < JUMP_DURATION; }

void Player::calVelocity(sf::Time dt) {
    auto length = static_pos - getPosition();
    if (isJumping()) {
        auto time_left = JUMP_DURATION - time_jumped;
        setVelocity({length.x / time_left.asSeconds(), length.y / time_left.asSeconds()});
        // The scale to ease the jumping movement
        // Derived from the formula: y = 1 - (x - 1)^2
        float scale = -2*((time_jumped.asSeconds() / JUMP_DURATION.asSeconds()) - 1);
        setVelocity(getVelocity() * scale);
        time_jumped += dt;

    } else {
        setVelocity({length.x / dt.asSeconds(), length.y / dt.asSeconds()});
    }
}

void Player::onJumpAnimationFinished() {
    animation = AnimationMachine(idle_texture, DEF_ANIMATION_DURATION, true);
}
