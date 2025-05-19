#ifndef RANDOM_H
#define RANDOM_H
#include <random>


inline int rand_int(const int left, const int right) {
    thread_local std::mt19937 gen{std::random_device{}()};
    std::uniform_int_distribution<int> dist(left, right);
    return dist(gen);
}

#endif //RANDOM_H
