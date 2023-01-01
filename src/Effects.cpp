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
    // 0 means stop immediately
    if ((wrapper && wrapper->times() == 0) || timesCurrent() == 0)
        return 0;
    return wrapper ? std::max(wrapper->times(), timesCurrent()) : timesCurrent();
}

void Effect::runMisc() const {
    runMiscCurrentBefore();
    if (wrapper) {
        wrapper->runMisc();
    }
    runMiscCurrentAfter();
}

std::unique_ptr<Effect> Effect::onEnd() const {
    auto end = onEndCurrent();
    if (end) {
        end->concat(wrapper ? wrapper->onEnd() : nullptr);
    } else {
        end = wrapper ? wrapper->onEnd() : nullptr;
    }
    return end;
}

std::unique_ptr<Effect> Effect::nextEffect() {
    auto next = nextEffectCurrent();
    if (next) {
        next->concat(wrapper ? wrapper->nextEffect() : nullptr);
    } else {
        next = wrapper ? wrapper->nextEffect() : nullptr;
    }
    return next;
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

std::unique_ptr<Effect> Effect::nextEffectCurrent() {
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

HealthEffect::HealthEffect(float healthDelta, bool reverse) : healthDelta_(healthDelta), reverse_(reverse) {}

float HealthEffect::healthDeltaCurrent() const {
    return healthDelta_;
}

std::unique_ptr<Effect> HealthEffect::onEndCurrent() const {
    if (reverse_) {
        return std::make_unique<HealthEffect>(-healthDelta_, false);
    } else {
        return Effect::onEndCurrent();
    }
}

SizeEffect::SizeEffect(sf::Vector2f sizeScale, bool reverse) : sizeScale_(sizeScale), reverse_(reverse) {}

sf::Vector2f SizeEffect::sizeScaleCurrent() const {
    return sizeScale_;
}

std::unique_ptr<Effect> SizeEffect::onEndCurrent() const {
    if (reverse_) {
        auto current = sizeScaleCurrent();
        return std::make_unique<SizeEffect>(sf::Vector2f(1 / current.x, 1 / current.y), false);
    } else {
        return Effect::onEndCurrent();
    }
}

DistanceEffect::DistanceEffect(sf::Vector2i distanceScale, bool reverse) : distanceScale_(distanceScale),
                                                                           reverse_(reverse) {}

sf::Vector2i DistanceEffect::distanceScaleCurrent() const {
    return distanceScale_;
}

std::unique_ptr<Effect> DistanceEffect::onEndCurrent() const {
    if (reverse_) {
        auto current = distanceScaleCurrent();
        return std::make_unique<DistanceEffect>(sf::Vector2i(1 / current.x, 1 / current.y), false);
    } else {
        return Effect::onEndCurrent();
    }
}

int InvincibleEffect::invincibleCurrent() const {
    return invincible_;
}

std::unique_ptr<Effect> InvincibleEffect::onEndCurrent() const {
    if (reverse_) {
        return std::make_unique<InvincibleEffect>(-invincible_, false);
    } else {
        return Effect::onEndCurrent();
    }
}

InvincibleEffect::InvincibleEffect(int invincible, bool reverse) : invincible_(invincible), reverse_(reverse) {}

DurationEffect::DurationEffect(sf::Time duration, int times, bool reverse) : durationEach_(duration), times_(times),
                                                                             reverse_(reverse) {}

sf::Time DurationEffect::durationEachCurrent() const {
    return durationEach_;
}

int DurationEffect::timesCurrent() const {
    return times_;
}

std::unique_ptr<Effect> DurationEffect::onEndCurrent() const {
    if (reverse_) {
        return std::make_unique<DurationEffect>(durationEach_, times_, false);
    } else {
        return Effect::onEndCurrent();
    }
}

float JumpDurationEffect::jumpDurationScaleCurrent() const {
    return jumpDurationScale_;
}

std::unique_ptr<Effect> JumpDurationEffect::onEndCurrent() const {
    if (reverse_) {
        return std::make_unique<JumpDurationEffect>(1 / jumpDurationScaleCurrent(), false);
    } else {
        return Effect::onEndCurrent();
    }
}

JumpDurationEffect::JumpDurationEffect(float jumpDurationScale, bool reverse) : jumpDurationScale_(jumpDurationScale),
                                                                                reverse_(reverse) {}

RunMiscEffect::RunMiscEffect(std::function<void()> before, std::function<void()> after) : before_(std::move(before)),
                                                                                          after_(std::move(after)) {}

RunMiscEffect::RunMiscEffect(std::function<void()> function) : after_(std::move(function)), before_() {}

void RunMiscEffect::runMiscCurrentBefore() const {
    if (before_) before_();
}

void RunMiscEffect::runMiscCurrentAfter() const {
    if (after_) after_();
}

std::unique_ptr<Effect> NextEffect::nextEffectCurrent() {
    return std::move(next_);
}

NextEffect::NextEffect(std::unique_ptr<Effect> next) : next_(std::move(next)) {}

void StopOnCommandEffect::stop() {
    stop_ = true;
}

int StopOnCommandEffect::timesCurrent() const {
    return stop_ ? 0 : Effect::timesCurrent();
}

std::unique_ptr<Effect> EffectFactory::create(EffectType type) {
    std::unique_ptr<Effect> effect = nullptr;
    switch (type) {
        case EffectType::HealthBoost:
            effect = std::make_unique<HealthEffect>(HEALTH_PER_FOOD, false);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, false));
            effect->concat(std::make_unique<RunMiscEffect>([]() {
                AudioController::instance().playSound(SoundEffect::Regen);
            }));
            break;
        case EffectType::SmallSizeBoost: {
            effect = std::make_unique<SizeEffect>(sf::Vector2f(SIZE_SMALLER_BOOST_SCALE, SIZE_SMALLER_BOOST_SCALE),
                                                  true);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, true));
            effect->concat(std::make_unique<DurationEffect>(SMALL_SIZE_BOOST_DURATION, 1, false));
            break;
        }
        case EffectType::SpeedBoost: {
            effect = std::make_unique<JumpDurationEffect>(JUMP_DURATION_BOOST_SCALE, true);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, true));
            effect->concat(std::make_unique<DurationEffect>(SPEED_BOOST_DURATION, 1, false));
            break;
        }
        case EffectType::InvincibleBoost: {
            effect = std::make_unique<InvincibleEffect>(1, true);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, true));
            effect->concat(std::make_unique<RunMiscEffect>([]() {
                AudioController::instance().playSound(SoundEffect::Invisible);
                }));
            effect->concat(std::make_unique<DurationEffect>(INVINCIBLE_BOOST_DURATION, 1, false));
            
            break;
        }
        case EffectType::Hungry: {
            effect = std::make_unique<HealthEffect>(HEALTH_REDUCTION_RATE, false);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(1), -1, false));
            break;
        }
        case EffectType::HitEnemy: {
            effect = std::make_unique<HealthEffect>(DAMAGE_PER_ENEMY, false);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, false));
            effect->concat(std::make_unique<RunMiscEffect>([]() {
                AudioController::instance().playSound(SoundEffect::Hitting);
            }));

            auto inv = std::make_unique<InvincibleEffect>(1, true);
            inv->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, true));
            inv->concat(std::make_unique<DurationEffect>(INVINCIBLE_AFTER_DAMAGED_DURATION, 1, false));
            effect->concat(std::make_unique<NextEffect>(std::move(inv)));
            break;
        }
        case EffectType::Drunk: {
            effect = std::make_unique<DistanceEffect>(sf::Vector2i(-1, -1), true);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(0), 1, true));
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(5), 1, false));
            break;
        }
        case EffectType::Drown: {
            effect = std::make_unique<HealthEffect>(HEALTH_REDUCTION_RATE_WHEN_DROWN, false);
            effect->concat(std::make_unique<DurationEffect>(sf::seconds(1), -1, false));
            break;
        }
        default:
            break;
    }
    return effect;
}