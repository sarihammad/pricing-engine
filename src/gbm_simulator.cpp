#include "gbm_simulator.hpp"
#include <cmath>
#include <chrono>

GBMSimulator::GBMSimulator(double spot,
                           double rate,
                           double vol,
                           double maturity,
                           int steps,
                           bool use_antithetic)
    : spot_(spot),
      rate_(rate),
      vol_(vol),
      maturity_(maturity),
      steps_(steps),
      use_antithetic_(use_antithetic),
      rng_(std::chrono::system_clock::now().time_since_epoch().count()),
      dist_(0.0, 1.0) {}

std::vector<std::vector<double>> GBMSimulator::generate_paths(int num_paths) {
    int effective_paths = use_antithetic_ ? num_paths / 2 : num_paths;
    double dt = maturity_ / static_cast<double>(steps_);

    std::vector<std::vector<double>> paths;
    paths.reserve(num_paths);

    for (int i = 0; i < effective_paths; ++i) {
        std::vector<double> path(steps_ + 1, spot_);
        std::vector<double> anti_path(steps_ + 1, spot_);

        for (int t = 1; t <= steps_; ++t) {
            double z = dist_(rng_);
            double drift = (rate_ - 0.5 * vol_ * vol_) * dt;
            double diffusion = vol_ * std::sqrt(dt) * z;

            path[t] = path[t - 1] * std::exp(drift + diffusion);

            if (use_antithetic_) {
                anti_path[t] = anti_path[t - 1] * std::exp(drift - diffusion);
            }
        }

        paths.push_back(std::move(path));
        if (use_antithetic_) {
            paths.push_back(std::move(anti_path));
        }
    }

    return paths;
}