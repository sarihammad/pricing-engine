#include <iostream>
#include <memory>
#include <iomanip>

#include "european_option.hpp"
#include "asian_option.hpp"
#include "barrier_option.hpp"
#include "pricing_engine.hpp"
#include "black_scholes.hpp"
#include "config.hpp"

int main() {
    // simulation configuration
    PricingConfig pricing_config {
        .spot_price = config::SPOT_PRICE,
        .risk_free_rate = config::RISK_FREE_RATE,
        .volatility = config::VOLATILITY,
        .maturity = config::TIME_TO_MATURITY,
        .num_steps = config::NUM_STEPS,
        .num_paths = config::NUM_PATHS,
        .use_antithetic = config::USE_ANTITHETIC
    };

    PricingEngine engine(pricing_config);

    std::cout << std::fixed << std::setprecision(4);

    // european option
    std::unique_ptr<Option> euro_call = std::make_unique<EuropeanOption>(config::STRIKE_PRICE, config::IS_CALL);
    double euro_price = engine.price(*euro_call);
    std::cout << "European Call Price: $" << euro_price << "\n";

    double bs_price = bs::price(
        config::SPOT_PRICE,
        config::STRIKE_PRICE,
        config::RISK_FREE_RATE,
        config::VOLATILITY,
        config::TIME_TO_MATURITY,
        config::IS_CALL
    );

    std::cout << "Black-Scholes Price: $" << bs_price << "\n";

    // asian option
    std::unique_ptr<Option> asian_call = std::make_unique<AsianOption>(config::STRIKE_PRICE, config::IS_CALL);
    double asian_price = engine.price(*asian_call);
    std::cout << "Asian Call Price: $" << asian_price << "\n";

    // barrier option 
    std::unique_ptr<Option> barrier_call = std::make_unique<BarrierOption>(
        config::STRIKE_PRICE,
        config::BARRIER_LEVEL,
        BarrierType::UpAndOut,
        config::IS_CALL
    );
    double barrier_price = engine.price(*barrier_call);
    std::cout << "Barrier Call Price: $" << barrier_price << "\n";

    return 0;
}
