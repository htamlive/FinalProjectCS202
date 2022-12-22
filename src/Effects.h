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

    virtual sf::Vector2i distanceScaleCurrent() const;

    virtual float jumpDurationScaleCurrent() const;

    virtual int invincibleCurrent() const;

    virtual sf::Time durationEachCurrent() const;

    /**
     * Return a zero or negative value to indicate a permanent boost.
     */
    virtual int timesCurrent() const;

    virtual void runMiscCurrentBefore() const;

    virtual void runMiscCurrentAfter() const;

    virtual std::unique_ptr<Effect> onEndCurrent() const;

public:
    Effect() = default;

    explicit Effect(std::unique_ptr<Effect> wrapper);

    void concat(std::unique_ptr<Effect> boost);

    float healthDelta() const;

    sf::Vector2f sizeScale() const;

    sf::Vector2i distanceScale() const;

    float jumpDurationScale() const;

    int invincible() const;

    sf::Time durationEach() const;

    int times() const;

    void runMisc() const;

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

class DistanceEffect : public Effect {
private:
    sf::Vector2i distanceScale_;

    sf::Vector2i distanceScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    DistanceEffect(sf::Vector2i distanceScale);
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
    int invincible_ = 1;

    int invincibleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    InvincibleEffect(int invincible);
};

class RunMiscEffect : public Effect {
private:
    std::function<void()> before_;
    std::function<void()> after_;

    void runMiscCurrentBefore() const override;

    void runMiscCurrentAfter() const override;

public:
    using Effect::Effect;

    RunMiscEffect(std::function<void()> before, std::function<void()> after);

    RunMiscEffect(std::function<void()> function);
};

class EffectFactory {
public:
    static std::unique_ptr<Effect> create(EffectType type);
};