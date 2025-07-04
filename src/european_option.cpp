#include "european_option.hpp"
#include <algorithm>

EuropeanOption::EuropeanOption(double strike, bool is_call)
    : strike_(strike), is_call_(is_call) {}

double EuropeanOption::payoff(const std::vector<double>& path) const {
    double final_price = path.back();
    if (is_call_) {
        return std::max(0.0, final_price - strike_);
    } else {
        return std::max(0.0, strike_ - final_price);
    }
}

bool EuropeanOption::is_call() const {
    return is_call_;
}