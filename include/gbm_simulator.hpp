#pragma once

/**
 * @file gbm_simulator.hpp
 * @brief Simulates geometric Brownian motion paths for asset price evolution.
 */

#include <vector>
#include <random>

class GBMSimulator {
public:
    /**
     * @brief Constructs a GBM simulator with given parameters.
     * @param spot Initial asset price.
     * @param rate Risk-free interest rate.
     * @param vol Volatility of returns.
     * @param maturity Time to maturity (in years).
     * @param steps Number of time steps.
     * @param use_antithetic Whether to use antithetic variates for variance reduction.
     */
    GBMSimulator(double spot,
                 double rate,
                 double vol,
                 double maturity,
                 int steps,
                 bool use_antithetic = false);

    /**
     * @brief Generates Monte Carlo paths of asset prices.
     * @param num_paths Number of price paths to simulate.
     * @return A vector of paths, each path is a vector of prices.
     */
    std::vector<std::vector<double>> generate_paths(int num_paths);

private:
    double spot_;
    double rate_;
    double vol_;
    double maturity_;
    int steps_;
    bool use_antithetic_;

    std::mt19937 rng_;
    std::normal_distribution<double> dist_;
};