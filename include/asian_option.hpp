#pragma once

/**
 * @file asian_option.hpp
 * @brief Concrete class for Asian-style options (average price).
 */

#include "option.hpp"

class AsianOption : public Option {
public:
    /**
     * @brief Constructs an Asian option.
     * @param strike The strike price.
     * @param is_call True if call, false if put.
     */
    AsianOption(double strike, bool is_call);

    /**
     * @brief Computes the payoff based on average price of the path.
     * @param path The full asset price path.
     * @return The payoff amount.
     */
    double payoff(const std::vector<double>& path) const override;

    /**
     * @brief Indicates whether the option is a call.
     * @return True if call, false if put.
     */
    bool is_call() const override;

private:
    double strike_;
    bool is_call_;
};