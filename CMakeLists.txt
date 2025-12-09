cmake_minimum_required(VERSION 3.16)
project(InventoryApp)

set(CMAKE_CXX_STANDARD 17)

# Qt installation path
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")

# Enable automatic Qt processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Qt5 Widgets
find_package(Qt5 COMPONENTS Widgets Core REQUIRED)

# ==========================================
# Main Application Executable
# ==========================================

add_executable(InventoryApp
    main.cpp
    src/MainWindow.cpp
    src/Inventory.cpp
    src/Item.cpp
    include/MainWindow.h
    include/Inventory.h
    include/Item.h
    ui/MainWindow.ui
)

target_include_directories(InventoryApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

set_target_properties(InventoryApp PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

target_link_libraries(InventoryApp
    Qt5::Widgets
    Qt5::Core
)

# ==========================================
# Google Test Setup
# ==========================================

option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
    enable_testing()

    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )

    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)

    # Test executable
    add_executable(InventoryAppTests
        tests/test_item.cpp
        tests/test_inventory.cpp
        src/Inventory.cpp
        src/Item.cpp
        include/Inventory.h
        include/Item.h
    )

    target_include_directories(InventoryAppTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    target_link_libraries(InventoryAppTests
        GTest::gtest_main
        Qt5::Core
    )

    include(GoogleTest)
    gtest_discover_tests(InventoryAppTests)

    message(STATUS "Google Test enabled - Run tests with: ctest or InventoryAppTests")
endif()

# ==========================================
# Summary
# ==========================================

message(STATUS "==============================================")
message(STATUS "InventoryApp Build Configuration")
message(STATUS "==============================================")
message(STATUS "Qt5 Path: ${CMAKE_PREFIX_PATH}")
message(STATUS "Build Tests: ${BUILD_TESTS}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "==============================================")
