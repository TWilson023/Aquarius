#ifndef PERLIN_NOISE
#define PERLIN_NOISE

#include <random>
#include <array>
#include <algorithm>
#include <time.h>

class Perlin {
public:
    Perlin(uint32_t seed=0);

    double noise(double x) const { return noise(x, 0, 0); }
    double noise(double x, double y) const { return noise(x, y, 0); }
    double noise(double x, double y, double z) const;

private:
    std::array<int, 512> p;
};

class PerlinOctave {
public:
    PerlinOctave(int octaves, uint32_t seed=0);

    double noise(double x) const { return noise(x, 0, 0); }
    double noise(double x, double y) const { return noise(x, y, 0); }
    double noise(double x, double y, double z) const;

private:
    Perlin perlin_;
    int octaves_;
};

#endif