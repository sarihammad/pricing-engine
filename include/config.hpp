#pragma once

/**
 * @file config.hpp
 * @brief Configuration constants for Monte Carlo Option Pricing.
 */

namespace config {

    // general parameters
    constexpr double SPOT_PRICE = 100.0; // current price of the underlying asset
    constexpr double STRIKE_PRICE = 100.0; // option strike price
    constexpr double RISK_FREE_RATE = 0.05; // annual risk-free interest rate (5%)
    constexpr double VOLATILITY = 0.2; // Annual volatility (20%)
    constexpr double TIME_TO_MATURITY = 1.0; // time to expiration in years
    constexpr int NUM_PATHS = 100000; // number of Monte Carlo simulation paths
    constexpr int NUM_STEPS = 252; // number of time steps per path

    // option type flags
    constexpr bool IS_CALL = true; // true = call option, false = Put option

    // barrier options
    constexpr double BARRIER_LEVEL = 110.0; // barrier level for barrier options

    // monte carlo control
    constexpr bool USE_ANTITHETIC = true; // use antithetic variates
    constexpr bool USE_CONTROL_VARIATE = true; // use control variate (for European options)

}
