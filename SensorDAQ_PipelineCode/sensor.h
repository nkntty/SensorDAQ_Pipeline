#pragma once
#include <random>
using namespace std;
// Base class (interface) for all sensors
class Sensor {
public:
    virtual double read() = 0;              // polymorphic function
    virtual ~Sensor() = default;            // important for base classes
};

// A sine wave sensor: A*sin(2*pi*f*t) + noise
class SineSensor : public Sensor {
public:
    SineSensor(double amplitude, double freq_hz, double dt, double noise_sigma);
    double read() override;

private:
    double A_;
    double f_;
    double dt_;
    double t_ = 0.0;

    mt19937 rng_;   //入れ物: std::mt19937 a high-quality pseudo-random number generator (PRNG) available in the C++ standard library since C++11
    
    //中身;  std::random_device provides a non-deterministic seed if available.
    normal_distribution<double> noise_; // mean=0, std=noise_sigma
};

// A slowly drifting temperature sensor: (base + drift) + noise
class TemperatureSensor : public Sensor {
public:
    TemperatureSensor(double ambient, double drift_per_sec, double dt, double noise_sigma);
    double read() override;

private:
    double ambient_;
    double drift_per_sec_;
    double dt_;
    double t_ = 0.0;

    mt19937 rng_;
    normal_distribution<double> noise_;
};

// A pressure sensor: baseline + small sinusoidal variation + noise
class PressureSensor : public Sensor {
public:
    PressureSensor(double baseline, double variation_amp, double variation_freq_hz,
                   double dt, double noise_sigma);
    double read() override;

private:
    double baseline_;
    double amp_;
    double f_;
    double dt_;
    double t_ = 0.0;

    mt19937 rng_;
    normal_distribution<double> noise_;

};
