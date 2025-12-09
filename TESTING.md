# 🧪 Testing Guide - InventoryApp with Google Test

This document explains how to build and run unit tests for InventoryApp using Google Test (GTest).

---

## 📁 Updated Project Structure

```
InventoryApp/
│
├── CMakeLists.txt              # Updated with GTest support
├── main.cpp
├── README.md
├── TESTING.md                  # This file
│
├── include/
│   ├── Item.h
│   ├── Inventory.h
│   └── MainWindow.h
│
├── src/
│   ├── Item.cpp
│   ├── Inventory.cpp
│   └── MainWindow.cpp
│
├── ui/
│   └── MainWindow.ui
│
└── tests/                      # NEW: Test directory
    ├── test_item.cpp           # Item class tests
    └── test_inventory.cpp      # Inventory class tests
```

---

## 🛠️ Prerequisites

### Required Software
- Everything from main README.md, plus:
- **Google Test** (automatically downloaded by CMake)
- Internet connection (first build only)

---

## 🚀 Building with Tests

### Option 1: Build Everything (App + Tests)

#### Windows (Qt Creator)
1. Open `CMakeLists.txt` in Qt Creator
2. Configure with your Qt kit
3. Build All (Ctrl+B)
4. You'll get:
   - `InventoryApp.exe` (main application)
   - `InventoryAppTests.exe` (test suite)

#### Windows (Command Line)
```cmd
cd "C:\Jenkins\IPC SAS\InventoryApp"
mkdir build
cd build

cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
cmake --build . --config Release

# Run tests
ctest -C Release --verbose
# OR
Release\InventoryAppTests.exe
```

#### Linux/macOS
```bash
cd /path/to/InventoryApp
mkdir build && cd build

cmake .. -DCMAKE_PREFIX_PATH="/path/to/Qt/5.15.2/gcc_64"
cmake --build .

# Run tests
ctest --verbose
# OR
./InventoryAppTests
```

---

### Option 2: Build Without Tests

If you don't want to build tests:

```bash
cmake .. -DBUILD_TESTS=OFF -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"
cmake --build .
```

---

## ▶️ Running Tests

### Method 1: Using CTest (Recommended)

```bash
cd build

# Run all tests
ctest

# Run with verbose output
ctest --verbose

# Run specific test
ctest -R ItemTest

# Run tests in parallel
ctest -j4
```

### Method 2: Direct Execution

#### Windows
```cmd
cd build\Release
InventoryAppTests.exe

# With GTest filters
InventoryAppTests.exe --gtest_filter=ItemTest.*
InventoryAppTests.exe --gtest_filter=InventoryTest.AddSingleItem
```

#### Linux/macOS
```bash
cd build
./InventoryAppTests

# With filters
./InventoryAppTests --gtest_filter=ItemTest.*
```

---

## 📊 Test Coverage

### Item Class Tests (test_item.cpp)

✅ **Constructor Tests**
- Default constructor
- Parameterized constructor
- Edge cases (empty name, zero price, negative price)

✅ **Getter Tests**
- getName()
- getPrice()

✅ **Edge Cases**
- Names with spaces
- Special characters
- Very large prices
- Price precision
- Unicode support

✅ **Copy Tests**
- Copy constructor behavior

**Total Item Tests: 19**

---

### Inventory Class Tests (test_inventory.cpp)

✅ **Constructor Tests**
- Default constructor
- Loading existing file

✅ **Add Item Tests**
- Single item
- Multiple items
- File persistence
- Zero price items

✅ **Delete Item Tests**
- Valid index deletion
- First/last item deletion
- Invalid indices (negative, too large)
- Empty inventory deletion
- File persistence

✅ **Load/Save Tests**
- Empty file
- Multiple entries
- Data replacement

✅ **Get Items Tests**
- Empty inventory
- Correct count
- Correct data

✅ **Integration Tests**
- Add-delete-add sequences
- Large inventory (100 items)
- Multi-operation persistence

**Total Inventory Tests: 28**

---

## 🎯 Test Output Examples

### Successful Run
```
[==========] Running 47 tests from 2 test suites.
[----------] Global test environment set-up.
[----------] 19 tests from ItemTest
[ RUN      ] ItemTest.DefaultConstructor
[       OK ] ItemTest.DefaultConstructor (0 ms)
[ RUN      ] ItemTest.ParameterizedConstructor
[       OK ] ItemTest.ParameterizedConstructor (0 ms)
...
[----------] 19 tests from ItemTest (5 ms total)

[----------] 28 tests from InventoryTest
[ RUN      ] InventoryTest.AddSingleItem
[       OK ] InventoryTest.AddSingleItem (2 ms)
...
[----------] 28 tests from InventoryTest (45 ms total)

[----------] Global test environment tear-down
[==========] 47 tests from 2 test suites ran. (50 ms total)
[  PASSED  ] 47 tests.
```

### Failed Test Example
```
[ RUN      ] ItemTest.GetPrice
test_item.cpp:45: Failure
Expected equality of these values:
  price
    Which is: 75.01
  75.00
[  FAILED  ] ItemTest.GetPrice (1 ms)
```

---

## 🔍 Advanced Testing

### Running Specific Test Suites

```bash
# Run only Item tests
./InventoryAppTests --gtest_filter=ItemTest.*

# Run only Inventory tests
./InventoryAppTests --gtest_filter=InventoryTest.*

# Run specific test
./InventoryAppTests --gtest_filter=ItemTest.DefaultConstructor
```

### Repeating Tests

```bash
# Run tests 10 times (useful for catching flaky tests)
./InventoryAppTests --gtest_repeat=10

# Run until failure
./InventoryAppTests --gtest_repeat=-1 --gtest_break_on_failure
```

### Shuffle Tests

```bash
# Run tests in random order
./InventoryAppTests --gtest_shuffle
```

### Generate XML Report

```bash
./InventoryAppTests --gtest_output=xml:test_results.xml
```

---

## 🐛 Debugging Failed Tests

### Step 1: Run with verbose output
```bash
./InventoryAppTests --gtest_filter=FailedTest.* --verbose
```

### Step 2: Add debug prints in test
```cpp
TEST_F(ItemTest, DebugTest) {
    Item item("Test", 10.0);
    std::cout << "Name: " << item.getName().toStdString() << std::endl;
    std::cout << "Price: " << item.getPrice() << std::endl;
    EXPECT_EQ(item.getName(), "Test");
}
```

### Step 3: Use debugger
- Set breakpoint in test file
- Run test in debug mode
- Step through code

---

## ✏️ Writing New Tests

### Basic Test Template

```cpp
#include <gtest/gtest.h>
#include "YourClass.h"

TEST(TestSuiteName, TestName) {
    // Arrange
    YourClass obj;
    
    // Act
    int result = obj.someMethod();
    
    // Assert
    EXPECT_EQ(result, expectedValue);
}
```

### Test Fixture Template

```cpp
class YourClassTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code before each test
    }

    void TearDown() override {
        // Cleanup code after each test
    }
    
    // Helper members/methods
    YourClass testObject;
};

TEST_F(YourClassTest, TestName) {
    EXPECT_TRUE(testObject.someMethod());
}
```

---

## 📋 Common GTest Assertions

### Boolean Conditions
```cpp
EXPECT_TRUE(condition);
EXPECT_FALSE(condition);
```

### Numeric Comparisons
```cpp
EXPECT_EQ(val1, val2);      // val1 == val2
EXPECT_NE(val1, val2);      // val1 != val2
EXPECT_LT(val1, val2);      // val1 < val2
EXPECT_LE(val1, val2);      // val1 <= val2
EXPECT_GT(val1, val2);      // val1 > val2
EXPECT_GE(val1, val2);      // val1 >= val2
```

### Floating Point
```cpp
EXPECT_DOUBLE_EQ(val1, val2);
EXPECT_NEAR(val1, val2, tolerance);
```

### String Comparisons
```cpp
EXPECT_STREQ(str1, str2);
EXPECT_STRNE(str1, str2);
```

### Fatal vs Non-Fatal
```cpp
ASSERT_*  // Stops test on failure
EXPECT_*  // Continues test on failure
```

---

## 🔧 Continuous Integration

### GitHub Actions Example

```yaml
name: Tests

on: [push, pull_request]

jobs:
  test:
    runs-on: ubuntu-latest
    steps:
      - uses: actions/checkout@v2
      - name: Install Qt
        run: sudo apt-get install qt5-default
      - name: Build
        run: |
          mkdir build && cd build
          cmake ..
          cmake --build .
      - name: Run tests
        run: cd build && ctest --verbose
```

---

## 📈 Test Coverage (Optional)

### Using gcov (Linux/macOS)

```bash
# Build with coverage flags
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage"
cmake --build .

# Run tests
./InventoryAppTests

# Generate coverage report
gcov ../src/*.cpp
```

### Using lcov for HTML report

```bash
lcov --capture --directory . --output-file coverage.info
genhtml coverage.info --output-directory coverage_html
```

---

## 🎓 Best Practices

1. ✅ **One assertion per test** (when possible)
2. ✅ **Test one thing at a time**
3. ✅ **Use descriptive test names**
4. ✅ **Follow AAA pattern** (Arrange, Act, Assert)
5. ✅ **Keep tests independent**
6. ✅ **Clean up test resources**
7. ✅ **Test edge cases**
8. ✅ **Don't test private methods directly**
9. ✅ **Mock external dependencies**
10. ✅ **Run tests frequently**

---

## 🚨 Troubleshooting

### Tests don't build

**Problem:** Google Test download fails
```
Solution: Check internet connection, or manually download GTest
```

**Problem:** Qt not found
```
Solution: Set CMAKE_PREFIX_PATH correctly in CMakeLists.txt
```

### Tests fail unexpectedly

**Problem:** File permission issues
```
Solution: Run tests with appropriate permissions
```

**Problem:** Test file conflicts
```
Solution: Ensure test files are cleaned up in TearDown()
```

---

## 📚 Resources

- [Google Test Documentation](https://google.github.io/googletest/)
- [Google Test Primer](https://google.github.io/googletest/primer.html)
- [Advanced GoogleTest Topics](https://google.github.io/googletest/advanced.html)

---

## 🎉 Summary

You now have:
- ✅ 47 unit tests covering Item and Inventory classes
- ✅ Automatic test discovery with CTest
- ✅ Easy integration with CI/CD
- ✅ Comprehensive test coverage
- ✅ Professional testing setup

Run tests before every commit to catch bugs early!

**Happy Testing! 🧪✨**
