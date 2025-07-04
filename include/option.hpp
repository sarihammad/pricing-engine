#pragma once

/**
 * @file option.hpp
 * @brief Abstract base class for financial options.
 */

#include <vector>

/**
 * @class Option
 * @brief Abstract base class representing a generic option contract.
 */
class Option {
public:
    virtual ~Option() = default;

    /**
     * @brief Computes the payoff for a single simulated path.
     * @param path A vector of asset prices over time.
     * @return The payoff value for that path.
     */
    virtual double payoff(const std::vector<double>& path) const = 0;

    /**
     * @brief Indicates whether this option is a call or a put.
     * @return true if call, false if put.
     */
    virtual bool is_call() const = 0;
};