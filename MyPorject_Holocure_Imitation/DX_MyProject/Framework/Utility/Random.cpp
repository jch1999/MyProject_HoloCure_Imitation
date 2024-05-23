#include "framework.h"

Random::Random()
{
}

Random::~Random()
{
}

int Random::GetRandomInt(int min, int max)
{
    std::mt19937_64 gen(rd());
    std::uniform_int_distribution<int> random_int(min, max);
    return random_int(gen);
}

float Random::GetRandomFloat(float min, float max)
{
    std::mt19937_64 gen(rd());
    std::uniform_real_distribution<float> random_int(min, max);
    return random_int(gen);
}
