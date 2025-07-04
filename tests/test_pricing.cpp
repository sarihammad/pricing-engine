#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>

#include "european_option.hpp"
#include "asian_option.hpp"
#include "barrier_option.hpp"
#include "black_scholes.hpp"
#include "pricing_engine.hpp"
#include "config.hpp"

TEST_CASE("European Call: Black-Scholes vs Monte Carlo", "[european]") {
    PricingConfig config;
    config.spot_price = config::SPOT_PRICE;
    config.risk_free_rate = config::RISK_FREE_RATE;
    config.volatility = config::VOLATILITY;
    config.maturity = config::TIME_TO_MATURITY;
    config.num_paths = config::NUM_PATHS;
    config.num_steps = config::NUM_STEPS;
    config.use_antithetic = config::USE_ANTITHETIC;

    EuropeanOption euro_call(config::STRIKE_PRICE, config::IS_CALL);
    PricingEngine engine(config);
    double mc_price = engine.price(euro_call);
    double bs_price = bs::price(
        config::SPOT_PRICE,
        config::STRIKE_PRICE,
        config::RISK_FREE_RATE,
        config::VOLATILITY,
        config::TIME_TO_MATURITY,
        config::IS_CALL
    );

    REQUIRE(mc_price == Catch::Approx(bs_price).margin(0.5));
}

TEST_CASE("Asian Call Monte Carlo within Reasonable Range", "[asian]") {
    PricingConfig config;
    config.spot_price = config::SPOT_PRICE;
    config.risk_free_rate = config::RISK_FREE_RATE;
    config.volatility = config::VOLATILITY;
    config.maturity = config::TIME_TO_MATURITY;
    config.num_paths = config::NUM_PATHS;
    config.num_steps = config::NUM_STEPS;
    config.use_antithetic = config::USE_ANTITHETIC;

    AsianOption asian_call(config::STRIKE_PRICE, config::IS_CALL);
    PricingEngine engine(config);
    double price = engine.price(asian_call);

    REQUIRE(price > 0.0);
    REQUIRE(price < 20.0);
}

TEST_CASE("Barrier Call Monte Carlo Rare Activation", "[barrier]") {
    PricingConfig config;
    config.spot_price = config::SPOT_PRICE;
    config.risk_free_rate = config::RISK_FREE_RATE;
    config.volatility = config::VOLATILITY;
    config.maturity = config::TIME_TO_MATURITY;
    config.num_paths = 50000; // as in your original test
    config.num_steps = config::NUM_STEPS;
    config.use_antithetic = config::USE_ANTITHETIC;

    BarrierOption barrier_call(
        config::STRIKE_PRICE, 
        config::BARRIER_LEVEL, 
        BarrierType::UpAndOut, 
        config::IS_CALL
    ); 
    
    PricingEngine engine(config);
    double price = engine.price(barrier_call);

    REQUIRE(price >= 0.0);
    REQUIRE(price < 5.0); 
}