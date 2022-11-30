#pragma once

#include <random>

class Random {
public:
    using value_type = double;

    /**
     * Uniform distribution between DOUBLE_MIN and DOUBLE_MAX.
     */
    Random();

    /**
     * Normal distribution with given mean and standard deviation.
     *
     * @param mean
     * @param stddev
     */
    Random(value_type mean, value_type stddev);

    /**
     * Normal distribution (kind of) with given mean, standard deviation, min and max.
     *
     * @param mean
     * @param stddev
     * @param min
     * @param max
     */
    Random(value_type mean, value_type stddev, value_type min, value_type max);

    template<typename T>
    T get() const;

    /**
     * Temporarily replaces predefined min and max values.
     */
    template<typename T>
    T get(T min, T max) const;

private:
    value_type mean, stddev, min, max;
};

template<typename T>
T Random::get() const {
    return get<T>(min, max);
}

template<typename T>
T Random::get(T min, T max) const {
    T res;
    do {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        std::normal_distribution<> d{mean, stddev};
        res = static_cast<T>(d(gen));
    } while (res < min || max < res);

    return res;
}
