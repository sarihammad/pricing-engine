# Monte Carlo Options Pricing Engine

An end-to-end options pricing system built in modern C++ to simulate and evaluate European, Asian, and Barrier options using Monte Carlo methods.

The engine supports variance reduction techniques and benchmarks its accuracy against the Black-Scholes model.


## Project Features

- Simulates Geometric Brownian Motion paths
- Supports:

  - European call & put options
  - Asian options (average price payoff)
  - Barrier options (Up-and-Out, Down-and-Out)

- Implements control variates and antithetic variates
- Compares with Black-Scholes closed-form solution
- Fully modular, testable C++ code with class-based design


## How to Run

```bash
mkdir build && cd build
cmake ..
make
```

1. Run the engine

```bash
./option_pricer
```

2. Run unit tests

```bash
ctest
```
