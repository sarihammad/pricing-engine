#include "asian_option.hpp"
#include <numeric>
#include <algorithm>

AsianOption::AsianOption(double strike, bool is_call)
    : strike_(strike), is_call_(is_call) {}

double AsianOption::payoff(const std::vector<double>& path) const {
    double average_price = std::accumulate(path.begin(), path.end(), 0.0) / path.size();
    if (is_call_) {
        return std::max(0.0, average_price - strike_);
    } else {
        return std::max(0.0, strike_ - average_price);
    }
}

bool AsianOption::is_call() const {
    return is_call_;
}