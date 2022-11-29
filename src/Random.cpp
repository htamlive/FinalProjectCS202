#include "Random.h"

#include <cmath>
#include <iostream>

Random::Random() : min(std::numeric_limits<double>::lowest()), max(std::numeric_limits<double>::max()) {
    mean = (max / 2.0) + (min / 2.0);
    stddev = (max / std::sqrtf(12)) - (min / std::sqrtf(12));
}

Random::Random(Random::value_type mean, Random::value_type stddev) : mean(mean), stddev(stddev),
                                                                     min(std::numeric_limits<double>::lowest()),
                                                                     max(std::numeric_limits<double>::max()) {}

Random::Random(Random::value_type mean, Random::value_type stddev, Random::value_type min, Random::value_type max)
        : mean(mean), stddev(stddev), min(min), max(max) {
    if (min > max) {
        std::cerr << "Random: min must be less than or equal to max.\n";
    }
}