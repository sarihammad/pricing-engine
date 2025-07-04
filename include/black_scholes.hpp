
#pragma once

/**
 * @file black_scholes.hpp
 * @brief Closed-form solution for pricing European options.
 */

namespace bs {

/**
 * @brief Computes the Black-Scholes price for a European option.
 * 
 * @param S     Spot price of the underlying asset
 * @param K     Strike price
 * @param r     Risk-free interest rate
 * @param sigma Volatility of the asset
 * @param T     Time to maturity (in years)
 * @param is_call True for call option, false for put
 * @return double Option price
 */
double price(double S, double K, double r, double sigma, double T, bool is_call);

} 