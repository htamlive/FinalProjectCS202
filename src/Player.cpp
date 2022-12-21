#include "Player.h"
#include "Consts.h"
#include "Entity.h"
#include "Enums.h"
//#include "PlayerEffect.h"
#include "PlayerState.h"
#include "SceneNode.h"
#include "World.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <cmath>
#include <iostream>
#include <memory>

void Player::updateCurrent(sf::Time dt) {
    if (isInvincible) {
        invincibleTime += dt;
        if (invincibleTime > invincibleDuration) {
            invincibleTime = sf::Time::Zero;
            isInvincible   = false;
        }
    }

    if (onSizeSmallerBoost) {
        localBounds = sizeBoostBounds;
        sizeBoostTime += dt;
        if (sizeBoostTime > sizeBoostDuration) {
            sizeBoostTime = sf::Time::Zero;
            onSizeSmallerBoost   = false;
            localBounds   = defaultBounds;
        }
    }

    if (onSpeedBoost) {
        speedBoostTime += dt;
        if (speedBoostTime > speedBoostDuration) {
            speedBoostTime = sf::Time::Zero;
            onSpeedBoost   = false;
        }
    }
    state->update(dt);
    health -= healthReductionRate * dt.asSeconds();
    if (health <= 0 && state->getStateID() != PlayerState::StateID::Dying) {
        health = 0;
        setState(new DyingState(this));
    }

    setVelocity(getVelocity() + woodVelocity);
    Entity::updateCurrent(dt);
    woodVelocity = {0, 0};
}

Player::Player()
    : jumpTexture(Texture::ID::PlayerJumpUp),
      idleTexture(Texture::ID::PlayerIdleUp), ripTexture(Texture::RIP),
      state(new IdleState(this)) {
    setState(new IdleState(this));
    animation = AnimationMachine(idleTexture, sf::seconds(5), true);
}

Player::Player(sf::Vector2f position, sf::Vector2f size)
    : Entity(Texture::ID::PlayerIdleUp, position, size, DEF_PLAYER_VELOCITY),
      jumpTexture(Texture::ID::PlayerJumpUp),
      idleTexture(Texture::ID::PlayerIdleUp),
      ripTexture(Texture::ID::RIP), state(new IdleState(this)) {
    setState(new IdleState(this));
    // TODO: hard coded
    setVelocity({0, 0});
    localBounds = sf::FloatRect(20, 20, GRID_SIZE.x - 40, GRID_SIZE.y - 40);
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    if (state->getStateID() == PlayerState::Jumping) {
        return;
    }
    auto newPos     = getPosition();
    auto currentPos = getPosition();
    if (state->getStateID() == PlayerState::Idle) {
        switch (event.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            newPos      = {currentPos.x, currentPos.y - GRID_SIZE.y};
            jumpTexture = Texture::ID::PlayerJumpUp;
            idleTexture = Texture::ID::PlayerIdleUp;
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            newPos      = {currentPos.x, currentPos.y + GRID_SIZE.y};
            jumpTexture = Texture::ID::PlayerJumpDown;
            idleTexture = Texture::ID::PlayerIdleDown;
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            newPos      = {currentPos.x - GRID_SIZE.x, currentPos.y};
            jumpTexture = Texture::ID::PlayerJumpLeft;
            idleTexture = Texture::ID::PlayerIdleLeft;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            newPos      = {currentPos.x + GRID_SIZE.x, currentPos.y};
            jumpTexture = Texture::ID::PlayerJumpRight;
            idleTexture = Texture::ID::PlayerIdleRight;
            break;
        default:
            break;
        }
        if (getPosition() != newPos) {
            newPos.x = newPos.x + getLocalBounds().width / 2;
            newPos.y = newPos.y + getLocalBounds().height / 2;
            newPos   = getNearestGridPosition(newPos);
            setState(new JumpingState(this, newPos));
        }
    }
}

void Player::onCollision(SceneNode *other) {
    if (other == collidingObstacle && other != nullptr) {
        return;
    }
    collidingObstacle = other;

    auto getDirection = [](sf::Vector2f v) {
        if (v.y == 0) {
            v.y = 0;
        } else {
            v.y = v.y / std::abs(v.y);
        }
        if (v.x == 0) {
            v.x = 0;
        } else {
            v.x = v.x / std::abs(v.x);
        }
        return v;
    };

    if (other->getCategory() == Category::Obstacle) {
        sf::Vector2f direction = -getDirection(getVelocity());
        auto         newPos    = getPosition() + direction * (GRID_SIZE.x / 2);
        setState(new ObstacleCollidingState(this, newPos));
    }

    if (other->getCategory() == Category::Enemy && !isInvincible) {
        auto enemy = dynamic_cast<Entity *>(other);
        if (enemy) {
            // A standing vehicle will not deal damage to the player, hence its
            // category is not Enemy
            if (enemy->getCategory() == Category::Enemy) {
                takeDamage(DAMAGE_PER_ENEMY);
            }
            sf::Vector2f direction =
                (enemy->getAbsPosition() - getAbsPosition());
            if (abs(direction.x) > abs(direction.y)) {
                direction.y = 0;
            } else {
                direction.x = 0;
            }
            direction           = -getDirection(direction);
            sf::Vector2f newPos = getPosition() + direction * (GRID_SIZE.x / 2);
            setState(new CollidingState(this, newPos));
        }
    }
}

Category::Type Player::getCategory() const { return Category::Player; }

void Player::setState(PlayerState *newState) {
    delete state;
    state = newState;
}

sf::FloatRect Player::getLocalBounds() const { return localBounds; }

sf::Vector2f Player::getNearestGridPosition(sf::Vector2f pos) const {
    auto absPos  = getAbsTransform() * pos;
    auto gridPos = getAbsTransform().getInverse() * absPos;
    gridPos.x    = std::round(gridPos.x / GRID_SIZE.x) * GRID_SIZE.x;
    gridPos.y    = std::round(gridPos.y / GRID_SIZE.y) * GRID_SIZE.y;
    return gridPos;
}

void Player::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates  states) const {
    auto sprite = animation.toSprite();
    sprite.setPosition(0, 0);
    if (onSizeSmallerBoost) {
        // TODO: 10 is hard coded
        sprite.setPosition(10, 10);
    }
    sprite.setScale(GRID_SIZE.x / sprite.getLocalBounds().width,
                    GRID_SIZE.y / sprite.getLocalBounds().height);
    sprite.setOrigin(sprite.getLocalBounds().width / 2,
                     sprite.getLocalBounds().height / 2);
    auto scale = sprite.getScale();
    if (onSizeSmallerBoost) {
        sprite.setScale(scale.x * SIZE_SMALLER_BOOST_SCALE, scale.y * SIZE_SMALLER_BOOST_SCALE);
    }
    sprite.setOrigin(0, 0);
    target.draw(sprite, states);

    drawHealthBar(target, states);
}

void Player::drawHealthBar(sf::RenderTarget &target,
                           sf::RenderStates  states) const {
    auto size_y = GRID_SIZE.x / 6;
    auto pos = sf::Vector2f(0, -GRID_SIZE.y / 2 - size_y / 2);

    sf::RectangleShape healthBar;
    healthBar.setSize(sf::Vector2f(GRID_SIZE.x, size_y));
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setPosition(pos);
    target.draw(healthBar, states);

    sf::RectangleShape healthBar2;
    healthBar2.setSize(sf::Vector2f((health / MAX_HEALTH) * GRID_SIZE.x, size_y));
    healthBar2.setFillColor(sf::Color::Green);
    healthBar2.setPosition(pos);
    target.draw(healthBar2, states);
}

void Player::takeSmallSizeBoost() { onSizeSmallerBoost = true; }
void Player::takeSpeedBoost() { onSpeedBoost = true; }

void Player::takeFood() {
    health += HEALTH_PER_FOOD;
    health = std::min(health, MAX_HEALTH);
}

void Player::takeDamage(float damage) {
    if (isInvincible) {
        return;
    }
    health -= damage;
    if (health <= 0) {
        health = 0;
        setState(new DeadState(this));
    }
}

bool Player::isDead() {
    return deadFlag;
}

void Player::onCollideWithWood(sf::Vector2f velocity) {
    woodVelocity = velocity;
}

void Player::saveCurrentNode(std::ostream &out) const {
    Entity::saveCurrentNode(out);
    out << health << " ";
    out << isInvincible << " ";
    out << onSizeSmallerBoost << " ";
    out << onSpeedBoost << " ";
    out << deadFlag << " ";
    out << woodVelocity.x << " " << woodVelocity.y << " ";
}

void Player::loadCurrentNode(std::istream &in) {
    Entity::loadCurrentNode(in);
    in >> health;
    in >> isInvincible;
    in >> onSizeSmallerBoost;
    in >> onSpeedBoost;
    in >> deadFlag;
    in >> woodVelocity.x;
    in >> woodVelocity.y;
}

std::string Player::getClassName() const {
    return "Player";
}
