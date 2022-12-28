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

static bool operator<(std::reference_wrapper<SceneNode const> lhs, std::reference_wrapper<SceneNode const> rhs) {
    return lhs.get() < rhs.get();
}

void Player::updateCurrent(sf::Time dt) {
    applyEffects(dt);
    state->update(dt);

    if (health <= 0 && state->getStateID() != PlayerState::StateID::Dying &&
        state->getStateID() != PlayerState::StateID::Dead) {
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
            distanceVec += {platformVelocity.x * JUMP_DURATION.asSeconds(),
                            platformVelocity.y * JUMP_DURATION.asSeconds()};
            distanceVec = {distanceVec.x * (float) distanceScale.x, distanceVec.y * (float) distanceScale.y};
            newPos += distanceVec;
        }
        if (getPosition() != newPos) {
            newPos.x = newPos.x + getLocalBounds().width / 2;
            newPos.y = newPos.y + getLocalBounds().height / 2;
            newPos = getNearestGridPosition(newPos);
            setState(new JumpingState(this, newPos));
        }
    }
}

Category::Type Player::getCategory() const { return Category::Player; }

void Player::setState(PlayerState *newState) {
    if (newState != nullptr) {
        delete state;
        state = newState;
    }
}

sf::Vector2f Player::getNearestGridPosition(sf::Vector2f pos) const {
    auto absPos = getAbsTransform() * pos;
    auto gridPos = getAbsTransform().getInverse() * absPos;
    gridPos.x = std::round(gridPos.x / GRID_SIZE.x) * GRID_SIZE.x;
    gridPos.y = std::round(gridPos.y / GRID_SIZE.y) * GRID_SIZE.y;
    return gridPos;
}

void Player::drawCurrent(sf::RenderTarget &target,
                         sf::RenderStates states) const {
    Entity::drawCurrent(target, states);
    drawHealthBar(target, states);
}

void Player::drawHealthBar(sf::RenderTarget &target,
                           sf::RenderStates states) const {
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

void Player::addHealth(float delta) {
    if (delta < 0) {
        if (!isInvincible())
            health += delta;
    } else {
        health += delta;
    }
    health = std::max((float) -1, std::min(MAX_HEALTH, health));
}

bool Player::isDead() {
    return deadFlag;
}

void Player::applyEffects(sf::Time dt) {
    float deltaHealth = 0, jumpScale = 1;
    sf::Vector2f sizeScale = {1, 1};
    sf::Vector2i distScale = {1, 1};
    int invincibleDelta = 0;
    std::vector<std::unique_ptr<Effect>> newEffects;


    auto apply = [&](Effect const &effect, unsigned int times) {
        deltaHealth += effect.healthDelta() * (float) times;
        sizeScale = {sizeScale.x * std::pow(effect.sizeScale().x, (float) times),
                     sizeScale.y * std::pow(effect.sizeScale().y, (float) times)};
        distScale = {distScale.x * (int) std::pow(effect.distanceScale().x, times),
                     distScale.y * (int) std::pow(effect.distanceScale().y, times)};
        jumpScale *= std::pow(effect.jumpDurationScale(), (float) times);
        invincibleDelta += effect.invincible();
        effect.runMisc();
    };

    for (auto &[effect, lasted, times]: effects) {
        lasted += dt;
        if (effect->times() == 0 ||
            (effect->times() >= 0 && times == effect->times() && lasted >= effect->durationEach())) {
            auto end = effect->onEnd();
            if (end) {
                newEffects.push_back(std::move(end));
            }
            auto next = effect->nextEffect();
            if (next) {
                newEffects.push_back(std::move(next));
            }
            times = -1;
        } else {
            int timesApply = 0;
            if (lasted >= effect->durationEach()) {
                timesApply = effect->durationEach() > sf::Time::Zero ? (int) (lasted / effect->durationEach()) : 1;
            } else if (times == 0) {
                timesApply = 1;
            }
            if (effect->times() > 0) {
                timesApply = std::min(timesApply, effect->times() - (int) times);
            }
            if (timesApply > 0) {
                apply(*effect, timesApply);
                times += timesApply;
                lasted = std::max(sf::Time::Zero, lasted - effect->durationEach() * (float) timesApply);
            }
        }
    }

    effects.erase(std::remove_if(effects.begin(), effects.end(),
                                 [](auto &b) {
                                     auto &[effect, lasted, times] = b;
                                     return times == (unsigned int) -1;
                                 }),
                  effects.end());

    invincibleBoostCount += invincibleDelta;
    addHealth(deltaHealth);
    distanceScale = {distanceScale.x * distScale.x, distanceScale.y * distScale.y};
    jumpDurationScale *= jumpScale;
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
    for (auto &effect: newEffects) {
        addEffect(std::move(effect));
    }
}

void Player::addEffect(std::unique_ptr<Effect> effect) {
    if (effect) {
        effects.emplace_back(std::move(effect), sf::Time::Zero, 0);
    }
}

bool Player::isInvincible() const {
    return invincibleBoostCount > 0;
}

sf::Vector2f Player::getDirectionVec() const {
    auto v = getVelocity();
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
}

void Player::addPlatformVelocity(sf::Vector2f velocity) {
    platformVelocity += velocity;
}

void Player::saveCurrentNode(std::ostream &out) const {
    Entity::saveCurrentNode(out);
    out << health << " ";
    // out << isInvincible << " ";
    // out << onSizeSmallerBoost << " ";
    // out << onSpeedBoost << " ";
    out << deadFlag << " ";
    out << woodVelocity.x << " " << woodVelocity.y << " ";
}

void Player::loadCurrentNode(std::istream &in) {
    Entity::loadCurrentNode(in);
    in >> health;
    // in >> isInvincible;
    // in >> onSizeSmallerBoost;
    // in >> onSpeedBoost;
    in >> deadFlag;
    in >> woodVelocity.x;
    in >> woodVelocity.y;
}

std::string Player::getClassName() const {
    return "Player";
}

bool Player::shouldSave() const {
    return true;
}
