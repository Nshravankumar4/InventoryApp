@echo off
REM ========================================
REM InventoryApp Test Runner for Windows
REM ========================================

echo.
echo ====================================
echo  InventoryApp - Google Test Runner
echo ====================================
echo.

REM Check if build directory exists
if not exist "build" (
    echo [INFO] Build directory not found. Creating...
    mkdir build
    cd build
    
    echo [INFO] Running CMake configuration...
    cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
    
    if errorlevel 1 (
        echo [ERROR] CMake configuration failed!
        pause
        exit /b 1
    )
    
    echo [INFO] Building project...
    cmake --build . --config Release
    
    if errorlevel 1 (
        echo [ERROR] Build failed!
        pause
        exit /b 1
    )
    
    cd ..
) else (
    echo [INFO] Build directory found. Rebuilding...
    cd build
    cmake --build . --config Release
    cd ..
)

echo.
echo ====================================
echo  Running Tests
echo ====================================
echo.

cd build

REM Run tests with CTest
echo [INFO] Running CTest...
ctest -C Release --verbose --output-on-failure

if errorlevel 1 (
    echo.
    echo [FAILED] Some tests failed!
    echo.
    echo Running detailed test output...
    Release\InventoryAppTests.exe
) else (
    echo.
    echo [SUCCESS] All tests passed!
)

cd ..

echo.
echo ====================================
echo  Test Run Complete
echo ====================================
echo.

pause