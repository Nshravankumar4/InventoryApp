#!/bin/bash

# ========================================
# InventoryApp Test Runner for Linux/macOS
# ========================================

echo ""
echo "===================================="
echo " InventoryApp - Google Test Runner"
echo "===================================="
echo ""

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Qt path - modify this for your system
QT_PATH="/path/to/Qt/5.15.2/gcc_64"

# Check if build directory exists
if [ ! -d "build" ]; then
    echo -e "${YELLOW}[INFO]${NC} Build directory not found. Creating..."
    mkdir build
    cd build
    
    echo -e "${YELLOW}[INFO]${NC} Running CMake configuration..."
    cmake .. -DCMAKE_PREFIX_PATH="$QT_PATH"
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}[ERROR]${NC} CMake configuration failed!"
        exit 1
    fi
    
    echo -e "${YELLOW}[INFO]${NC} Building project..."
    cmake --build .
    
    if [ $? -ne 0 ]; then
        echo -e "${RED}[ERROR]${NC} Build failed!"
        exit 1
    fi
    
    cd ..
else
    echo -e "${YELLOW}[INFO]${NC} Build directory found. Rebuilding..."
    cd build
    cmake --build .
    cd ..
fi

echo ""
echo "===================================="
echo " Running Tests"
echo "===================================="
echo ""

cd build

# Run tests with CTest
echo -e "${YELLOW}[INFO]${NC} Running CTest..."
ctest --verbose --output-on-failure

if [ $? -ne 0 ]; then
    echo ""
    echo -e "${RED}[FAILED]${NC} Some tests failed!"
    echo ""
    echo "Running detailed test output..."
    ./InventoryAppTests
else
    echo ""
    echo -e "${GREEN}[SUCCESS]${NC} All tests passed!"
fi

cd ..

echo ""
echo "===================================="
echo " Test Run Complete"
echo "===================================="
echo ""
