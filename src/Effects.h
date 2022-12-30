#pragma once

#include <algorithm>

#include "Enums.h"
#include <functional>
#include <memory>

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
     * Return a negative value to indicate a permanent boost.
     */
    virtual int timesCurrent() const;

    virtual void runMiscCurrentBefore() const;

    virtual void runMiscCurrentAfter() const;

    virtual std::unique_ptr<Effect> onEndCurrent() const;

    virtual std::unique_ptr<Effect> nextEffectCurrent();

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

    std::unique_ptr<Effect> nextEffect();

    virtual ~Effect() = default;
};

class DurationEffect : public Effect {
private:
    sf::Time durationEach_ = sf::Time::Zero;
    int times_ = -1;
    bool reverse_ = true;

    sf::Time durationEachCurrent() const override;

    int timesCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    explicit DurationEffect(sf::Time duration, int times, bool reverse = true);
};

class HealthEffect : public Effect {
private:
    float healthDelta_ = 0;
    bool reverse_ = true;

    float healthDeltaCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    HealthEffect(float healthDelta, bool reverse = true);
};

class SizeEffect : public Effect {
private:
    sf::Vector2f sizeScale_ = {1, 1};
    bool reverse_ = true;

    sf::Vector2f sizeScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    SizeEffect(sf::Vector2f sizeScale, bool reverse = true);
};

class DistanceEffect : public Effect {
private:
    sf::Vector2i distanceScale_ = {1, 1};
    bool reverse_ = true;

    sf::Vector2i distanceScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    DistanceEffect(sf::Vector2i distanceScale, bool reverse = true);
};

class JumpDurationEffect : public Effect {
private:
    float jumpDurationScale_ = 1;
    bool reverse_ = true;

    float jumpDurationScaleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    JumpDurationEffect(float jumpDurationScale, bool reverse = true);
};

class InvincibleEffect : public Effect {
private:
    int invincible_ = 1;
    bool reverse_ = true;

    int invincibleCurrent() const override;

    std::unique_ptr<Effect> onEndCurrent() const override;

public:
    using Effect::Effect;

    InvincibleEffect(int invincible, bool reverse = true);
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

class NextEffect : public Effect {
private:
    std::unique_ptr<Effect> next_;

    std::unique_ptr<Effect> nextEffectCurrent() override;

public:
    using Effect::Effect;

    explicit NextEffect(std::unique_ptr<Effect> nextEffect);
};

class StopOnCommandEffect : public Effect {
private:
    bool stop_ = false;

    int timesCurrent() const override;

public:
    using Effect::Effect;

    void stop();
};

class EffectFactory {
public:
    static std::unique_ptr<Effect> create(EffectType type);
};
