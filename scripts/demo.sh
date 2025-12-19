#!/bin/bash

set -e

BUILD_DIR="./build"
SOURCE_FILE="example/main.cpp"
OUTPUT_BIN="demo_app"

GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}[1/5] Building tools (Pass + Runtime)...${NC}"
mkdir -p $BUILD_DIR
cd $BUILD_DIR
cmake .. > /dev/null
make -j$(nproc)
cd ..

echo -e "${BLUE}[2/5] Generating Bitcode from victim program...${NC}"
clang -emit-llvm -c $SOURCE_FILE -o main.bc

echo -e "${BLUE}[3/5] Injecting telemetry (The Surgeon)...${NC}"
opt -load-pass-plugin=$BUILD_DIR/injector/TelemetryInjector.so \
    -passes="telemetry-injector" \
    main.bc -o main.inst.bc

echo -e "${BLUE}[4/5] Linking with measurement library (The Lab)...${NC}"
clang main.inst.bc -L$BUILD_DIR/runtime -lProfilerRuntime -o $OUTPUT_BIN -lstdc++

echo -e "${BLUE}[5/5] Running...${NC}"
echo -e "${GREEN}----------------------------------------${NC}"
./$OUTPUT_BIN
echo -e "${GREEN}----------------------------------------${NC}"
