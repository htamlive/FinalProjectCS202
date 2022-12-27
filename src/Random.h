#pragma once

#include <random>
#include <iostream>

/**
 * A wrapper to pass on RandomNumberDistribution machines.
 */
template<class RandomNumberDistribution>
class Random {
public:
    /**
     * Uniform distribution between DOUBLE_MIN and DOUBLE_MAX.
     */
    Random();

    Random(RandomNumberDistribution distribution);

    template<typename TResult>
    TResult get();

    /**
     * Only accepts value between min and max.
     */
    template<typename TResult>
    TResult get(TResult min, TResult max);

    void save(std::ostream& out = std::cout) const;

    void load(std::istream& in = std::cin);

private:
    RandomNumberDistribution distribution;
};

template<class RandomNumberDistribution>
void Random<RandomNumberDistribution>::save(std::ostream &out) const {
    //TODO: how to save a distribution?
}

template<class RandomNumberDistribution>
void Random<RandomNumberDistribution>::load(std::istream &in) {
    //TODO: how to load a distribution?
}

template<class RandomNumberDistribution>
Random<RandomNumberDistribution>::Random(RandomNumberDistribution distribution) : distribution(distribution) {}

template<class RandomNumberDistribution>
Random<RandomNumberDistribution>::Random() {
    distribution = RandomNumberDistribution();
}

template<class RandomNumberDistribution>
template<typename TResult>
TResult Random<RandomNumberDistribution>::get() {
    return get(std::numeric_limits<TResult>::lowest(), std::numeric_limits<TResult>::max());
}

template<class RandomNumberDistribution>
template<typename TResult>
TResult Random<RandomNumberDistribution>::get(TResult min, TResult max) {
    TResult res;
    do {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        res = static_cast<TResult>(distribution(gen));
    } while (res < min || max < res);

    return res;
}
