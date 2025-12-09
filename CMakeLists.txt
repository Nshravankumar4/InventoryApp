cmake_minimum_required(VERSION 3.16)
project(InventoryApp)

set(CMAKE_CXX_STANDARD 17)

# Qt installation path
set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")

# Enable automatic processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Find Qt5 Widgets
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Define all files
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

# Include directories
target_include_directories(InventoryApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}
)

# Tell AutoUIC where to find .ui files
set_target_properties(InventoryApp PROPERTIES
    AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
)

# Link Qt
target_link_libraries(InventoryApp Qt5::Widgets)
