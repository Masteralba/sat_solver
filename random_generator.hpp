#pragma once
#include <random>

// Объявляем генератор как extern
extern std::mt19937 random_engine;

// Функции для удобства
void init_random_engine();
int random_int(int min, int max);