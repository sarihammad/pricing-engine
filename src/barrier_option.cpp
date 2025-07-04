#include "barrier_option.hpp"
#include <algorithm>

BarrierOption::BarrierOption(double strike,
                             double barrier,
                             BarrierType barrier_type,
                             bool is_call)
    : strike_(strike),
      barrier_(barrier),
      barrier_type_(barrier_type),
      is_call_(is_call) {}

double BarrierOption::payoff(const std::vector<double>& path) const {
    double max_price = *std::max_element(path.begin(), path.end());
    double min_price = *std::min_element(path.begin(), path.end());

    bool knocked_out = false;

    if (barrier_type_ == BarrierType::UpAndOut && max_price >= barrier_) {
        knocked_out = true;
    }
    if (barrier_type_ == BarrierType::DownAndOut && min_price <= barrier_) {
        knocked_out = true;
    }

    if (knocked_out) return 0.0;

    double final_price = path.back();
    return is_call_ ? std::max(0.0, final_price - strike_)
                    : std::max(0.0, strike_ - final_price);
}

bool BarrierOption::is_call() const {
    return is_call_;
}