# Binpacking

## Supported algorithms

- **First Fit Decreasing Height**
- **Best Fit Decreasing Height**
- **Worst Fit Decreasing Height**
- **Next Fit Decreasing Height**

## Building

### Requirements

- CMake 3.15 or higher
- C17 compiler (gcc, clang, msvc, etc.)

### Building

```bash
mkdir build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

## Running all algorithms

```bash
./binpacking cmp <float/int> <num iterations>
```
Results will be in CSV format on stdout.

## Running a single algorithm

```bash
./binpacking <algorithm> <float/int> <num iterations>
```
It checks if the algorithm is valid (no overlap between rectangles and all rectangles are inside the bin). If it is invalid, it will print the error and exit.
