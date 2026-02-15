#pragma once
#include <deque> //std::dequeは両端への高速な挿入・削除とランダムアクセスができる双方向キュー
using namespace std;
// Base class (interface) for filters
class Filter {
public:
    virtual double apply(double x) = 0;
    virtual ~Filter() = default;
};

// Returns input unchanged
class NoFilter : public Filter {
public:
    double apply(double x) override { return x; }
};

// Moving average of the last N samples
class MovingAverageFilter : public Filter {
public:
    explicit MovingAverageFilter(size_t window); // window: the size of the number of buf
    double apply(double x) override;

private:
    size_t window_;
    deque<double> buf_;
    double sum_ = 0.0;
};

// Simple 1st-order low-pass: y = alpha*x + (1-alpha)*y_prev
class LowPassFilter : public Filter {
public:
    explicit LowPassFilter(double alpha);
    double apply(double x) override;

private:
    double alpha_;
    bool has_prev_ = false;
    double y_prev_ = 0.0;
};
