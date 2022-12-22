#include <algorithm>
#include <utility>

#include "Effects.h"
#include "Consts.h"
#include "AudioController.h"

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

sf::Vector2i Effect::distanceScale() const {
    auto scale = wrapper ? wrapper->distanceScale() : sf::Vector2i(1, 1);
    auto current = distanceScaleCurrent();
    return {scale.x * current.x, scale.y * current.y};
}

float Effect::jumpDurationScale() const {
    return (wrapper ? wrapper->jumpDurationScale() : 1) * jumpDurationScaleCurrent();
}

int Effect::invincible() const {
    return (wrapper ? wrapper->invincible() : 0) + invincibleCurrent();
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

sf::Vector2i Effect::distanceScaleCurrent() const {
    return {1, 1};
}

int Effect::invincibleCurrent() const {
    return 0;
}

std::unique_ptr<Effect> Effect::onEndCurrent() const {
    return std::make_unique<Effect>();
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

void Effect::runMiscCurrentBefore() const {}

void Effect::runMiscCurrentAfter() const {}

void Effect::runMisc() const {
    runMiscCurrentBefore();
    if (wrapper) {
        wrapper->runMisc();
    }
    runMiscCurrentAfter();
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

DistanceEffect::DistanceEffect(sf::Vector2i distanceScale) : distanceScale_(distanceScale) {}

sf::Vector2i DistanceEffect::distanceScaleCurrent() const {
    return distanceScale_;
}

std::unique_ptr<Effect> DistanceEffect::onEndCurrent() const {
    auto current = distanceScaleCurrent();
    return std::make_unique<DistanceEffect>(sf::Vector2i(1 / current.x, 1 / current.y));
}

int InvincibleEffect::invincibleCurrent() const {
    return invincible_;
}

std::unique_ptr<Effect> InvincibleEffect::onEndCurrent() const {
    return std::make_unique<InvincibleEffect>(-invincible_);
}

InvincibleEffect::InvincibleEffect(int invincible) : invincible_(invincible) {}

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

RunMiscEffect::RunMiscEffect(std::function<void()> before, std::function<void()> after) : before_(std::move(before)), after_(std::move(after)) {}

RunMiscEffect::RunMiscEffect(std::function<void()> function) : after_(std::move(function)), before_() {}

void RunMiscEffect::runMiscCurrentBefore() const {
    if (before_) before_();
}

void RunMiscEffect::runMiscCurrentAfter() const {
    if (after_) after_();
}

std::unique_ptr<Effect> EffectFactory::create(EffectType type) {
    std::unique_ptr<Effect> effect = nullptr;
    switch (type) {
        case EffectType::HealthBoost:
            effect = std::make_unique<HealthEffect>(HEALTH_PER_FOOD);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1));
            effect->concat(std::make_unique<RunMiscEffect>([]() {
                AudioController::instance().playSound(SoundEffect::Regen);
            }));
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
        case EffectType::Drunk: {
            effect = std::make_unique<DistanceEffect>(sf::Vector2i(-1, -1));
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(5), 1));
            break;
        }
        default:
            break;
    }
    return effect;
}