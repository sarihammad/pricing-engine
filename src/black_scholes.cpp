#include "black_scholes.hpp"
#include <cmath>
#include <algorithm>

namespace {

double norm_cdf(double x) {
    return 0.5 * std::erfc(-x / std::sqrt(2));
}

} 

namespace bs {

double price(double S, double K, double r, double sigma, double T, bool is_call) {
    if (T <= 0 || sigma <= 0) {
        return std::max((is_call ? S - K : K - S), 0.0);
    }

    double d1 = (std::log(S / K) + (r + 0.5 * sigma * sigma) * T) / 
                (sigma * std::sqrt(T));
    double d2 = d1 - sigma * std::sqrt(T);

    if (is_call) {
        return S * norm_cdf(d1) - K * std::exp(-r * T) * norm_cdf(d2);
    } else {
        return K * std::exp(-r * T) * norm_cdf(-d2) - S * norm_cdf(-d1);
    }
}

}