#include <chrono>

#include "random_generator.hpp"

// Определяем генератор
std::mt19937 random_engine;

void init_random_engine() {
    // Инициализируем с помощью high-resolution clock
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    random_engine.seed(seed);
}

int random_int(int min, int max) {
    std::uniform_int_distribution<int> dist(min, max);
    return dist(random_engine);
}