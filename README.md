[![CI](https://github.com/hollannikas/pajatsinko/actions/workflows/ci.yml/badge.svg)](https://github.com/hollannikas/pajatsinko/actions/workflows/ci.yml)

# Pajatsinko (C++ learning project)

I wanted to try out what modern C++ feels like after a 25‑year break. This little project is a simple pachinko/pajatso simulator I used to re‑acquaint myself with the language, toolchain, testing, and CI.


## What it is
- A tiny C++20 project that simulates dropping a ball through a triangular peg board (pajatso/galton‑like).
- Clean separation of logic and app:
  - `pachinko_lib`: core classes (`Peg`, `Board`).
  - `pachinko`: small console app that visualizes one ball drop and prints the path/slot.
- Unit tests with GoogleTest.


## Why this project
- Personal experiment to see how C++ feels today (CMake, testing, IDEs, CI) compared to decades ago.
- Keep it small, readable, and with a feedback loop (tests + CI) so iteration is quick.


## How to run the tests
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target test_pachinko
ctest --test-dir build --output-on-failure
```

## How to build
```
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --target pachinko
./build/pachinko
```

## Continuous Integration
A GitHub Actions workflow runs on pushes and pull requests:
- File: `.github/workflows/ci.yml`
- It configures with CMake, builds `test_pachinko`, and runs tests with `ctest` on Ubuntu.


## Project layout
- `include/` – Public headers (`board.h`, `peg.h`).
- `src/` – Implementations (`board.cpp`, `peg.cpp`, `main.cpp`).
- `tests/` – GoogleTest unit tests.
- `CMakeLists.txt` – Project and target definitions.
- `.github/workflows/ci.yml` – CI configuration.

## Example output
A typical run prints a simple board visualization, the path (L/R choices), and the final slot:
```
🎰 Pachinko Board

Board (o = ball hit, . = peg):

     o 
    . o 
   . . o 
  . . o . 
 . . o . . 
1 2 3 4 5 6 
Ball path: R R L L R 
Ball landed in slot: 4
```
(Output varies since hits are random unless forced.)


## Notes
- Requires a compiler with C++20 support.
- Tests use GoogleTest fetched via CMake’s `FetchContent`, so no manual test deps are needed.
- You can force deterministic paths in tests via `Board::setHitSequence`.
