#include "sensor.h"
#include <cmath> // <cmath> for PI, sin(), cos(), tan()
using namespace std;
static constexpr double PI = 3.14159265358979323846;
//std::random_deviceで「最初の種（シード）」を作り、それを使ってstd::mt19937という「高速なエンジン」を回す. 組み合わせることで鳥早くかつランダムになる. 初期値をseedと呼ぶ

SineSensor::SineSensor(double amplitude, double freq_hz, double dt, double noise_sigma)
    : A_(amplitude),
      f_(freq_hz),
      dt_(dt),
      rng_(random_device{}()),  //std::random_device provides a non-deterministic seed if available.
      //a high-quality pseudo-random number generator (PRNG) available in the C++ standard library since C++11
      noise_(0.0, noise_sigma) {} // mean=0, std=noise_sigma

double SineSensor::read() {
    double true_value = A_ * sin(2.0 * PI * f_ * t_);
    t_ += dt_;
    return true_value + noise_(rng_);
}

TemperatureSensor::TemperatureSensor(double ambient, double drift_per_sec, double dt, double noise_sigma)
    : ambient_(ambient),
      drift_per_sec_(drift_per_sec),
      dt_(dt),
      rng_(random_device{}()),
      noise_(0.0, noise_sigma) {}

double TemperatureSensor::read() {
    // true temp drifts linearly with time (toy model)
    double true_value = ambient_ + drift_per_sec_ * t_;
    t_ += dt_;
    return true_value + noise_(rng_);
}

PressureSensor::PressureSensor(double baseline, double variation_amp, double variation_freq_hz,
                               double dt, double noise_sigma)
    : baseline_(baseline),
      amp_(variation_amp),
      f_(variation_freq_hz),
      dt_(dt),
      rng_(random_device{}()),
      noise_(0.0, noise_sigma) {}

double PressureSensor::read() {
    double true_value = baseline_ + amp_ * sin(2.0 * PI * f_ * t_); //amp=振幅
    t_ += dt_;
    return true_value + noise_(rng_);
}
