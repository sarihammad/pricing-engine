#include "pricing_engine.hpp"
#include <cmath>
#include <numeric>

PricingEngine::PricingEngine(PricingConfig config)
    : config_(std::move(config)),
      rng_(std::random_device{}()),
      norm_dist_(0.0, 1.0) {}

std::vector<std::vector<double>> PricingEngine::simulate_paths(bool antithetic) {
    int N = config_.num_steps;
    int M = config_.num_paths;
    double dt = config_.maturity / N;
    double drift = (config_.risk_free_rate - 0.5 * config_.volatility * config_.volatility) * dt;
    double diffusion = config_.volatility * std::sqrt(dt);

    std::vector<std::vector<double>> paths;
    paths.reserve(antithetic ? M * 2 : M);

    for (int i = 0; i < M; ++i) {
        std::vector<double> path(N + 1, config_.spot_price);
        std::vector<double> anti_path(N + 1, config_.spot_price);

        for (int t = 1; t <= N; ++t) {
            double z = norm_dist_(rng_);
            path[t] = path[t - 1] * std::exp(drift + diffusion * z);
            if (antithetic) {
                anti_path[t] = anti_path[t - 1] * std::exp(drift - diffusion * z);
            }
        }

        paths.push_back(std::move(path));
        if (antithetic) {
            paths.push_back(std::move(anti_path));
        }
    }

    return paths;
}

double PricingEngine::price(const Option& option) {
    auto paths = simulate_paths(config_.use_antithetic);
    double payoff_sum = 0.0;

    for (const auto& path : paths) {
        payoff_sum += option.payoff(path);
    }

    double discounted_avg = (payoff_sum / paths.size()) * std::exp(-config_.risk_free_rate * config_.maturity);
    return discounted_avg;
}