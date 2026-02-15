#include "filter.h"
#include <algorithm>
#include <stdexcept> //invalid_arguemnt
using namespace std;
MovingAverageFilter::MovingAverageFilter(size_t window) : window_(window) {
    if (window_ == 0) throw invalid_argument("MovingAverageFilter window must be >= 1");
    // std::invalid_arguemnt  the function has been called with an argument that is the correct type but has an inappropriate value. 
}

double MovingAverageFilter::apply(double x) {
    buf_.push_back(x);
    sum_ += x;

    if (buf_.size() > window_) {
        sum_ -= buf_.front();
        buf_.pop_front();
    }
    return sum_ / static_cast<double>(buf_.size()); //static_cast<double>(expression) is the preferred, explicit way to convert a value or expression to the double
}

LowPassFilter::LowPassFilter(double alpha) : alpha_(alpha) {
    if (alpha_ < 0.0 || alpha_ > 1.0) throw invalid_argument("LowPassFilter alpha must be in [0,1]");
}

double LowPassFilter::apply(double x) {
    if (!has_prev_) {
        has_prev_ = true;
        y_prev_ = x;
        return y_prev_;
    }
    y_prev_ = alpha_ * x + (1.0 - alpha_) * y_prev_;
    return y_prev_;
}
//LPF:: a circuit or signal processing algorithm that allows signals below a specific cutoff frequency to pass through while attenuating (weakening) signals with frequencies higher than that threshold.