#pragma once

/**
 * @file european_option.hpp
 * @brief Concrete class for European-style call and put options.
 */

#include "option.hpp"

class EuropeanOption : public Option {
public:
    /**
     * @brief Constructs a European option.
     * @param strike The strike price of the option.
     * @param is_call True if it's a call option, false if put.
     */
    EuropeanOption(double strike, bool is_call);

    /**
     * @brief Computes the payoff for a given path (last price).
     * @param path The asset price path.
     * @return The payoff value.
     */
    double payoff(const std::vector<double>& path) const override;

    /**
     * @brief Indicates whether this option is a call.
     * @return True if call, false if put.
     */
    bool is_call() const override;

private:
    double strike_;
    bool is_call_;
};