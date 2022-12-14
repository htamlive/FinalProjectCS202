#include "Player.h"
#include "Consts.h"
#include "Enums.h"
#include "PlayerState.h"
#include "SceneNode.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include <memory>

void Player::updateCurrent(sf::Time dt) {
    state->update(dt);
    Entity::updateCurrent(dt);
}

Player::Player()
    : jumpTexture(Texture::ID::PlayerJumpUp),
      idleTexture(Texture::ID::PlayerIdleUp), state(new IdleState(this)) {
    staticPos = getPosition();
    setState(new IdleState(this));
    animation = AnimationMachine(idleTexture, sf::seconds(5), true);
}

Player::Player(sf::Vector2f position, sf::Vector2f size)
    : Entity(Texture::ID::PlayerIdleUp, position, size, DEF_PLAYER_VELOCITY),
      jumpTexture(Texture::ID::PlayerJumpUp),
      idleTexture(Texture::ID::PlayerIdleUp), state(new IdleState(this)) {
    setState(new IdleState(this));
    staticPos = getPosition();
    setVelocity({0, 0});
    adjustBounds(20, 20, 40, 40);
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    if (!dynamic_cast<IdleState *>(state)) {
        return;
    }
    auto newPos = staticPos;
    if (dynamic_cast<IdleState *>(state)) {
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
        staticPos = newPos;
        setState(new JumpingState(this));
    }
}

void Player::onCollision(SceneNode *other) {
    if (dynamic_cast<IdleState *>(state)) {
        return;
    }
    if (dynamic_cast<JumpingState *>(state)) {
        setState(new CollidingState(this));
        setVelocity({0, 0});
        staticPos = preJumpPos;
    }
}

Category::Type Player::getCategory() const { return Category::Player; }

void Player::setState(PlayerState *newState) {
    delete state;
    state = newState;
}
