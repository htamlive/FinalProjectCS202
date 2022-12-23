#include "Player.h"
#include "Consts.h"
#include "Entity.h"
#include "Enums.h"
#include "PlayerState.h"
#include "SceneNode.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>

#include <cmath>
#include <iostream>
#include <memory>

static bool operator <(std::reference_wrapper<SceneNode const> lhs, std::reference_wrapper<SceneNode const> rhs) {
    return lhs.get() < rhs.get();
}

void Player::updateCurrent(sf::Time dt) {
    processCollisions();

    applyEffects(dt);
    state->update(dt);

    if (health <= 0 && state->getStateID() != PlayerState::StateID::Dying && state->getStateID() != PlayerState::StateID::Dead) {
        if (!this->deadFlag)
            health = 0;
        setState(new DyingState(this));
    }

    Entity::updateCurrent(dt);
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
    setVelocity({0, 0});
    localBounds = sf::FloatRect(size.x / 64 * 20, size.y / 64 * 20, size.x / 64 * 24, size.y / 64 * 24);
}

void Player::onKeyPressed(sf::Event::KeyEvent event) {
    if (state->getStateID() == PlayerState::Idle) {
        sf::Vector2f distanceVec = {0, 0};
        switch (event.code) {
        case sf::Keyboard::W:
        case sf::Keyboard::Up:
            distanceVec = {0, -GRID_SIZE.y};
            jumpTexture = Texture::ID::PlayerJumpUp;
            idleTexture = Texture::ID::PlayerIdleUp;
            break;
        case sf::Keyboard::S:
        case sf::Keyboard::Down:
            distanceVec = {0, GRID_SIZE.y};
            jumpTexture = Texture::ID::PlayerJumpDown;
            idleTexture = Texture::ID::PlayerIdleDown;
            break;
        case sf::Keyboard::A:
        case sf::Keyboard::Left:
            distanceVec = {-GRID_SIZE.x, 0};
            jumpTexture = Texture::ID::PlayerJumpLeft;
            idleTexture = Texture::ID::PlayerIdleLeft;
            break;
        case sf::Keyboard::D:
        case sf::Keyboard::Right:
            distanceVec = {GRID_SIZE.x, 0};
            jumpTexture = Texture::ID::PlayerJumpRight;
            idleTexture = Texture::ID::PlayerIdleRight;
            break;
        default:
            break;
        }

        auto newPos = getPosition();
        if (distanceVec != sf::Vector2f(0, 0)) {
            distanceVec += {platformVelocity.x * JUMP_DURATION.asSeconds(), platformVelocity.y * JUMP_DURATION.asSeconds()};
            distanceVec = {distanceVec.x * (float)distanceScale.x, distanceVec.y * (float)distanceScale.y};
            newPos += distanceVec;
        }
        if (getPosition() != newPos) {
            newPos.x = newPos.x + getLocalBounds().width / 2;
            newPos.y = newPos.y + getLocalBounds().height / 2;
            newPos   = getNearestGridPosition(newPos);
            setState(new JumpingState(this, newPos));
        }
    }
}

void Player::onCollision(const SceneNode *other) {
    if (other == nullptr) return;
    colliding.insert(*other);
}

void Player::processCollisions() {
    // TODO: Handle exception where the pointer has been destroyed.
    erase_if(lastCollided, [&](auto &other) {
        if (!colliding.contains(other)) {
            onEndCollision(other);
            return true;
        }
        return false;
    });

    for(auto &other : colliding) {
        if (lastCollided.contains(other)) {
            onRepeatCollision(other);
        }
        else {
            onNewCollision(other);
            lastCollided.insert(other);
        }
    }

    colliding.clear();
}

void Player::onNewCollision(const SceneNode &other) {
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

    if (other.getCategory() == Category::Obstacle) {
        sf::Vector2f direction = -getDirection(getVelocity());
        auto         newPos    = getPosition() + direction * (GRID_SIZE.x / 2);
        setState(new ObstacleCollidingState(this, newPos));
    }
    else if (other.getCategory() == Category::Enemy && !isInvincible()) {
        auto &enemy = dynamic_cast<Entity const &>(other);
        // A standing vehicle will not deal damage to the player, hence its
        // category is not Enemy
        if (enemy.getCategory() == Category::Enemy) {
            takeDamage();
        }
        sf::Vector2f direction = enemy.getAbsPosition() - getAbsPosition();
        if (abs(direction.x) > abs(direction.y)) {
            direction.y = 0;
        } else {
            direction.x = 0;
        }
        direction           = -getDirection(direction);
        sf::Vector2f newPos = getPosition() + direction * (GRID_SIZE.x / 2);
        setState(new CollidingState(this, newPos));
    }
    else if (other.getCategory() == Category::Wood) {
        auto &wood = dynamic_cast<Entity const &>(other);
        platformVelocity += wood.getVelocity();
    }
}

void Player::onRepeatCollision(const SceneNode &other) {}

void Player::onEndCollision(const SceneNode &other) {
    if (other.getCategory() == Category::Wood) {
        auto &wood = dynamic_cast<Entity const &>(other);
        platformVelocity -= wood.getVelocity();
    }
}

Category::Type Player::getCategory() const { return Category::Player; }

void Player::setState(PlayerState *newState) {
    delete state;
    state = newState;
}

sf::Vector2f Player::getNearestGridPosition(sf::Vector2f pos) const {
    auto absPos  = getAbsTransform() * pos;
    auto gridPos = getAbsTransform().getInverse() * absPos;
    gridPos.x    = std::round(gridPos.x / GRID_SIZE.x) * GRID_SIZE.x;
    gridPos.y    = std::round(gridPos.y / GRID_SIZE.y) * GRID_SIZE.y;
    return gridPos;
}

void Player::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates  states) const {
    Entity::drawCurrent(target, states);
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

void Player::takeDamage() {
    if (isInvincible()) {
        return;
    }
    addEffect(EffectFactory::create(EffectType::HitEnemy));
}

bool Player::isDead() {
    return deadFlag;
}

void Player::applyEffects(sf::Time dt) {
    auto apply = [&](Effect const &effect, unsigned int times) {
        health = std::max((float)-1, std::min(MAX_HEALTH, health + effect.healthDelta() * (float)times));

        sf::Vector2f sizeScale = {std::powf(effect.sizeScale().x, (float)times), std::powf(effect.sizeScale().y, (float)times)};
        {
            auto &bounds = localBounds;
            sf::Vector2f center = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
            bounds.width *= sizeScale.x;
            bounds.height *= sizeScale.y;
            bounds.left = center.x - bounds.width / 2;
            bounds.top = center.y - bounds.height / 2;
        }
        {
            auto &bounds = spriteBounds;
            sf::Vector2f center = {bounds.left + bounds.width / 2, bounds.top + bounds.height / 2};
            bounds.width *= sizeScale.x;
            bounds.height *= sizeScale.y;
            bounds.left = center.x - bounds.width / 2;
            bounds.top = center.y - bounds.height / 2;
        }

        sf::Vector2i moreDist = {(int)std::pow(effect.distanceScale().x, times), (int)std::pow(effect.distanceScale().y, times)};
        distanceScale = {distanceScale.x * moreDist.x, distanceScale.y * moreDist.y};

        jumpDurationScale *= std::powf(effect.jumpDurationScale(), (float)times);

        invincibleBoostCount += effect.invincible();

        effect.runMisc();
    };

    for(auto &[effect, lasted, times] : effects) {
        lasted += dt;
        if (effect->times() > 0 && times == effect->times() && lasted >= effect->durationEach()) {
            auto end = effect->onEnd();
            if (end) {
                apply(*end, 1);
            }
            times = -1;
        }
        else {
            int timesApply = 0;
            if (lasted >= effect->durationEach()) {
                timesApply = effect->durationEach() > sf::Time::Zero ? (int)(lasted / effect->durationEach()) : 1;
            } else if (times == 0) {
                timesApply = 1;
            }
            if (effect->times() > 0) {
                timesApply = std::min(timesApply, effect->times() - (int)times);
            }
            if (timesApply > 0) {
                apply(*effect, timesApply);
                times += timesApply;
                lasted = std::max(sf::Time::Zero, lasted - effect->durationEach() * (float)timesApply);
            }
        }
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(),
                                [](auto &b) {
        auto &[effect, lasted, times] = b;
        return times == (unsigned int)-1;
    }),
                 effects.end());
}

void Player::addEffect(std::unique_ptr<Effect> effect) {
    if (effect) {
        effects.emplace_back(std::move(effect), sf::Time::Zero, 0);
    }
}

bool Player::isInvincible() const {
    return invincibleBoostCount > 0;
}