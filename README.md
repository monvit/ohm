# Ohm

A "white-box" profiler built on top of the LLVM infrastructure. Unlike sampling profilres (e.g., `perf`), **Ohm** modifies the program's Intermediate Representation (IR) during compilation to inject precise measurement probes. It turns opaque binaries into transparent systems that report their own execution metrics.

## Architecture

The project follows a dual-component architecture design to separate instrumentation logic from measurement logic.

### The Injector (LLVM Pass)
- **Role:** The "Surgeon".
- **Time:** Compile-time.
- **Function:** Analysis the LLVM IR, identifies function entry and exit points (Basic Blocks), and injects calls to the runtime library. It does not measure anything itself; it merely prepares the code.

### The Runtime Library
- **Role:** The "Lab".
- **Time:** Runtime.
- **Function:** A lightweight static library linked to the target binary. It implements the probes, captures CPU cycle counts, and aggregates statistics.

## Prerequisites
- **LLVM & Clang**
- **CMake** (3.13+)
- **C++ Compiler** supporting C++17/20

## Build Instructions

#### 1. Clone & enter repo
```bash
git clone https://github.com/monvit/ohm.git monvit-ohm && cd monvit-ohm
```

#### 2. Prepare build directory
```bash
mkdir build && cd build
```

#### 3. Configure with Cmake
```bash
cmake ..
```

#### 4. Build the Pass and Runtime
```bash
cmake --build .
```

## Usage

To instrument a target program (e.g., `examples/main.cc`):

#### 1. Compile to Bitcode
```bash
clang -emit-llvm -c main.cpp -o main.bc
```

#### 2. Load the Pass and Instrument
```bash
opt -load-pass-plugin=./injector/libOhmPass.so -passes="ohm" main.bc -o main_inst.bc
```

#### 3. Link with Runtime and Compile to Executable:
```bash
clang main_inst.bc -L./runtime -lmonvit_rt -o my_program
```

#### 4. Run
```bash
./my_program
```
