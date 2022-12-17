#pragma once

#include <algorithm>

#include "Enums.h"

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

class Effect {
private:
    std::unique_ptr<Effect> wrapper = nullptr;

protected:
    virtual float healthDeltaCurrent() const;

    virtual sf::Vector2f sizeScaleCurrent() const;

    virtual sf::Vector2f velocityScaleCurrent() const;

    virtual float jumpDurationScaleCurrent() const;

    virtual bool invincibleCurrent() const;

    virtual sf::Time durationEachCurrent() const;

    /**
     * Return a zero or negative value to indicate a permanent boost.
     */
    virtual int timesCurrent() const;

    virtual std::unique_ptr<Effect> onEndCurrent() const;

public:
    Effect() = default;

    explicit Effect(std::unique_ptr<Effect> wrapper);

    void concat(std::unique_ptr<Effect> boost);

    float healthDelta() const;

    sf::Vector2f sizeScale() const;

    sf::Vector2f velocityScale() const;

    float jumpDurationScale() const;

    bool invincible() const;

    sf::Time durationEach() const;

    int times() const;

    std::unique_ptr<Effect> onEnd() const;

    virtual ~Effect() = default;
};

class DurationEffect : public Effect {
private:
    sf::Time durationEach_;

    int times_;

    sf::Time durationEachCurrent() const override;

    int timesCurrent() const override;

public:
    using Effect::Effect;
    explicit DurationEffect(sf::Time duration, int times);
};

class HealthEffect : public Effect {
private:
    float healthDelta_ = 0;

    float healthDeltaCurrent() const override;

public:
    using Effect::Effect;

    HealthEffect(float healthDelta);
};

class SizeEffect : public Effect {
private:
    sf::Vector2f sizeScale_ = {1, 1};

    sf::Vector2f sizeScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    SizeEffect(sf::Vector2f sizeScale);
};

class VelocityEffect : public Effect {
private:
    sf::Vector2f velocityScale_;

    sf::Vector2f velocityScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    VelocityEffect(sf::Vector2f velocityScale);
};

class JumpDurationEffect : public Effect {
private:
    float jumpDurationScale_;

    float jumpDurationScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    JumpDurationEffect(float jumpDurationScale);
};

class InvincibleEffect : public Effect {
private:
    bool invincible_;

    bool invincibleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    InvincibleEffect();

    InvincibleEffect(bool invincible);
};

class EffectFactory {
public:
    static std::unique_ptr<Effect> create(EffectType type);
};