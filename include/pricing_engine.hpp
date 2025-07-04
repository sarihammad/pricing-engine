#pragma once

/**
 * @file pricing_engine.hpp
 * @brief Monte Carlo option pricing engine with support for variance reduction.
 */

#include "option.hpp"
#include <vector>
#include <random>

struct PricingConfig {
    double spot_price;
    double risk_free_rate;
    double volatility;
    double maturity;
    int num_steps;
    int num_paths;
    bool use_antithetic;
};

/**
 * @class PricingEngine
 * @brief Simulates paths and prices options using Monte Carlo.
 */
class PricingEngine {
public:
    /**
     * @brief Constructs the engine with simulation parameters.
     * @param config Struct with all pricing parameters.
     */
    explicit PricingEngine(PricingConfig config);

    /**
     * @brief Prices an option using Monte Carlo simulation.
     * @param option The option to price.
     * @return Estimated option value.
     */
    double price(const Option& option);

private:
    PricingConfig config_;
    std::mt19937 rng_;
    std::normal_distribution<> norm_dist_;

    std::vector<std::vector<double>> simulate_paths(bool antithetic = false);
};