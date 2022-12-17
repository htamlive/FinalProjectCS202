#include <algorithm>

#include "Effects.h"
#include "Consts.h"

Effect::Effect(std::unique_ptr<Effect> wrapper) : wrapper(std::move(wrapper)) {}

void Effect::concat(std::unique_ptr<Effect> effect) {
    if (wrapper) {
        wrapper->concat(std::move(effect));
    } else {
        wrapper = std::move(effect);
    }
}

float Effect::healthDelta() const {
    return (wrapper ? wrapper->healthDelta() : 0) + healthDeltaCurrent();
}

sf::Vector2f Effect::sizeScale() const {
    auto scale = wrapper ? wrapper->sizeScale() : sf::Vector2f(1, 1);
    auto current = sizeScaleCurrent();
    return {scale.x * current.x, scale.y * current.y};
}

sf::Vector2f Effect::velocityScale() const {
    auto scale = wrapper ? wrapper->velocityScale() : sf::Vector2f(1, 1);
    auto current = velocityScaleCurrent();
    return {scale.x * current.x, scale.y * current.y};
}

float Effect::jumpDurationScale() const {
    return (wrapper ? wrapper->jumpDurationScale() : 1) * jumpDurationScaleCurrent();
}

bool Effect::invincible() const {
    return wrapper != nullptr && wrapper->invincible() || invincibleCurrent();
}

sf::Time Effect::durationEach() const {
    return wrapper ? std::max(wrapper->durationEach(), durationEachCurrent()) : durationEachCurrent();
}

int Effect::times() const {
    return wrapper ? std::max(wrapper->times(), timesCurrent()) : timesCurrent();
}

std::unique_ptr<Effect> Effect::onEnd() const {
    auto end = onEndCurrent();
    if (wrapper) {
        end->concat(wrapper->onEnd());
    }
    return end;
}

float Effect::healthDeltaCurrent() const {
    return 0;
}

sf::Vector2f Effect::sizeScaleCurrent() const {
    return {1, 1};
}

sf::Vector2f Effect::velocityScaleCurrent() const {
    return {1, 1};
}

bool Effect::invincibleCurrent() const {
    return false;
}

std::unique_ptr<Effect> Effect::onEndCurrent() const {
    auto ptr = std::make_unique<Effect>();
    return std::move(ptr);
}

sf::Time Effect::durationEachCurrent() const {
    return sf::Time::Zero;
}

int Effect::timesCurrent() const {
    return -1;
}

float Effect::jumpDurationScaleCurrent() const {
    return 1;
}

HealthEffect::HealthEffect(float healthDelta) : healthDelta_(healthDelta) {}

float HealthEffect::healthDeltaCurrent() const {
    return healthDelta_;
}

SizeEffect::SizeEffect(sf::Vector2f sizeScale) : sizeScale_(sizeScale) {}

sf::Vector2f SizeEffect::sizeScaleCurrent() const {
    return sizeScale_;
}

std::unique_ptr<Effect> SizeEffect::onEndCurrent() const {
    auto current = sizeScaleCurrent();
    return std::make_unique<SizeEffect>(sf::Vector2f(1 / current.x, 1 / current.y));
}

VelocityEffect::VelocityEffect(sf::Vector2f velocityScale) : velocityScale_(velocityScale) {}

sf::Vector2f VelocityEffect::velocityScaleCurrent() const {
    return velocityScale_;
}

std::unique_ptr<Effect> VelocityEffect::onEndCurrent() const {
    auto current = velocityScaleCurrent();
    return std::move(std::make_unique<VelocityEffect>(sf::Vector2f(1 / current.x, 1 / current.y)));
}

bool InvincibleEffect::invincibleCurrent() const {
    return true;
}

std::unique_ptr<Effect> InvincibleEffect::onEndCurrent() const {
    return std::make_unique<InvincibleEffect>(false);
}

InvincibleEffect::InvincibleEffect(bool invincible) : invincible_(invincible) {}

InvincibleEffect::InvincibleEffect() : InvincibleEffect(true) {}

DurationEffect::DurationEffect(sf::Time duration, int times) : durationEach_(duration), times_(times) {}

sf::Time DurationEffect::durationEachCurrent() const {
    return durationEach_;
}

int DurationEffect::timesCurrent() const {
    return times_;
}

float JumpDurationEffect::jumpDurationScaleCurrent() const {
    return jumpDurationScale_;
}

std::unique_ptr<Effect> JumpDurationEffect::onEndCurrent() const {
    return std::make_unique<JumpDurationEffect>(1 / jumpDurationScaleCurrent());
}

JumpDurationEffect::JumpDurationEffect(float jumpDurationScale) {
    jumpDurationScale_ = jumpDurationScale;
}

std::unique_ptr<Effect> EffectFactory::create(EffectType type) {
    std::unique_ptr<Effect> effect = nullptr;
    switch (type) {
        case EffectType::HealthBoost:
            effect = std::make_unique<HealthEffect>(HEALTH_PER_FOOD);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1));
            break;
        case EffectType::SmallSizeBoost: {
            effect = std::make_unique<SizeEffect>(sf::Vector2f(0.5, 0.5));
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(5), 1));
            break;
        }
        case EffectType::SpeedBoost: {
            effect = std::make_unique<JumpDurationEffect>(0.5);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(5), 1));
            break;
        }
        case EffectType::InvincibleBoost: {
            effect = std::make_unique<InvincibleEffect>();
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(5), 1));
            break;
        }
        case EffectType::Hungry: {
            effect = std::make_unique<HealthEffect>(HEALTH_REDUCTION_RATE);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(1), 0));
            break;
        }
        case EffectType::HitEnemy: {
            effect = std::make_unique<HealthEffect>(DAMAGE_PER_ENEMY);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1));
            break;
        }
        default:
            break;
    }
    return effect;
}