#pragma once

/**
 * @file barrier_option.hpp
 * @brief Knock-out barrier option implementation (up-and-out / down-and-out).
 */

#include "option.hpp"

enum class BarrierType {
    UpAndOut,
    DownAndOut
};

/**
 * @class BarrierOption
 * @brief A European-style option with knock-out barrier condition.
 */
class BarrierOption : public Option {
public:
    /**
     * @brief Constructs a Barrier Option.
     * @param strike Strike price of the option.
     * @param barrier Barrier level (knock-out).
     * @param barrier_type Type of barrier (UpAndOut / DownAndOut).
     * @param is_call True if call, false if put.
     */
    BarrierOption(double strike,
                  double barrier,
                  BarrierType barrier_type,
                  bool is_call);

    /**
     * @brief Computes the barrier-adjusted payoff for a price path.
     * @param path The full asset price path.
     * @return Payoff value (0 if barrier breached).
     */
    double payoff(const std::vector<double>& path) const override;

    /**
     * @brief Whether the option is a call.
     * @return True if call, false if put.
     */
    bool is_call() const override;

private:
    double strike_;
    double barrier_;
    BarrierType barrier_type_;
    bool is_call_;
};