# InventoryApp - Qt5 Inventory Management System

A simple, modern inventory management application built with Qt5 and C++17.

## 📋 Features

- ✅ Add new inventory items with name and price
- ✅ View all inventory items in a list
- ✅ Delete items from inventory
- ✅ Persistent storage using text file
- ✅ Clean Qt Widgets GUI interface 
- ✅ Modern CMake build system

---

## 🗂️ Project Structure

```
InventoryApp/
│
├── CMakeLists.txt          # CMake build configuration
├── main.cpp                # Application entry point
├── README.md               # This file
│
├── include/                # Header files
│   ├── Item.h              # Item class definition
│   ├── Inventory.h         # Inventory manager class
│   └── MainWindow.h        # Main window UI class
│
├── src/                    # Source files
│   ├── Item.cpp            # Item implementation
│   ├── Inventory.cpp       # Inventory implementation
│   └── MainWindow.cpp      # Main window implementation
│
└── ui/                     # Qt Designer UI files
    └── MainWindow.ui       # Main window UI layout
```

---

## 🛠️ Prerequisites

### Required Software

- **Qt 5.15.2** (or later Qt5 version)
  - Qt Widgets module
- **CMake 3.16** or higher
- **C++17 compatible compiler**
  - Windows: MSVC 2019/2022
  - Linux: GCC 7+ or Clang 5+
  - macOS: Xcode 10+

### Qt Installation Path

Default path used in this project:
```
C:/Qt/5.15.2/msvc2019_64
```

If your Qt is installed elsewhere, update line 7 in `CMakeLists.txt`:
```cmake
set(CMAKE_PREFIX_PATH "YOUR_QT_PATH_HERE")
```

---

## 🚀 Building the Project

### Method 1: Using Qt Creator (Recommended for Windows)

1. **Open Qt Creator**
2. **File → Open File or Project**
3. Select `CMakeLists.txt` from the project root
4. Configure the project (select your Qt kit)
5. Click **Build** (Ctrl+B / Cmd+B)
6. Click **Run** (Ctrl+R / Cmd+R)

### Method 2: Command Line (Windows)

```cmd
cd "C:\Jenkins\IPC SAS\InventoryApp"

# Create build directory
mkdir build
cd build

# Configure CMake
cmake .. -G "Visual Studio 16 2019" -A x64 -DCMAKE_PREFIX_PATH="C:/Qt/5.15.2/msvc2019_64"

# Build
cmake --build . --config Release

# Run
Release\InventoryApp.exe
```

### Method 3: Command Line (Linux/macOS)

```bash
cd /path/to/InventoryApp

# Create build directory
mkdir build
cd build

# Configure CMake
cmake .. -DCMAKE_PREFIX_PATH="/path/to/Qt/5.15.2/gcc_64"

# Build
cmake --build .

# Run
./InventoryApp
```

---

## 📝 Usage

### Adding an Item
1. Click **"Add Item"** button
2. Enter the item name (e.g., "Laptop")
3. Enter the item price (e.g., 999.99)
4. Item will be saved automatically

### Viewing Items
- Items are displayed automatically in the list widget
- Click **"View Items"** to refresh the list
- Format: `1. ItemName | Price: 999.99`

### Deleting an Item
1. Click **"Delete Item"** button
2. Enter the item number to delete (e.g., 1, 2, 3...)
3. Item will be removed and file updated

### Data Storage
- All items are saved in `inventory.txt` in the application directory
- Format: `ItemName Price` (space-separated)
- Example:
  ```
  Laptop 999.99
  Mouse 25.50
  Keyboard 75.00
  ```

---

## 🔧 Troubleshooting

### Problem: `ui_MainWindow.h` not found

**Solution:**
1. Delete the `build/` or `out/` folder completely
2. Reconfigure CMake
3. Ensure `CMAKE_AUTOUIC ON` is set in CMakeLists.txt
4. Verify `MainWindow.ui` exists in `ui/` folder

### Problem: Cannot access private member `Item::name`

**Solution:**
- Use getter methods: `item.getName()` and `item.getPrice()`
- Never access `item.name` or `item.price` directly

### Problem: CMake cannot find Qt5

**Solution:**
1. Set `CMAKE_PREFIX_PATH` to your Qt installation:
   ```cmake
   set(CMAKE_PREFIX_PATH "C:/Qt/5.15.2/msvc2019_64")
   ```
2. Or set environment variable:
   ```cmd
   set CMAKE_PREFIX_PATH=C:\Qt\5.15.2\msvc2019_64
   ```

### Problem: AutoUIC cannot find MainWindow.ui

**Solution:**
- Ensure `AUTOUIC_SEARCH_PATHS` is set in CMakeLists.txt:
  ```cmake
  set_target_properties(InventoryApp PROPERTIES
      AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui"
  )
  ```

---

## 🏗️ Architecture

### Class Diagram

```
┌─────────────┐
│    Item     │
├─────────────┤
│ - name      │
│ - price     │
├─────────────┤
│ + getName() │
│ + getPrice()│
└─────────────┘
       ▲
       │
       │ uses
       │
┌─────────────────┐
│   Inventory     │
├─────────────────┤
│ - items         │
├─────────────────┤
│ + loadItems()   │
│ + saveItems()   │
│ + addItem()     │
│ + deleteItem()  │
│ + getItems()    │
└─────────────────┘
       ▲
       │
       │ uses
       │
┌─────────────────┐
│   MainWindow    │
├─────────────────┤
│ - ui            │
│ - inventory     │
├─────────────────┤
│ + on_addButton  │
│ + on_viewButton │
│ + on_deleteBtn  │
└─────────────────┘
```

### File Interaction Flow

```
User Input (Qt GUI)
    ↓
MainWindow.cpp
    ↓
Inventory.cpp (manages items)
    ↓
Item.cpp (data model)
    ↓
inventory.txt (persistent storage)
```

---

## 📦 Dependencies

- **Qt5::Widgets** - GUI components
- **Qt5::Core** - Core Qt functionality
- **C++ Standard Library** - File I/O (`<fstream>`)

---

## 🔮 Future Enhancements

- [ ] Add search/filter functionality
- [ ] Add item categories
- [ ] Add item quantity tracking
- [ ] Export to CSV/Excel
- [ ] Add item images
- [ ] Use SQLite database instead of text file
- [ ] Add user authentication
- [ ] Multi-language support
- [ ] Print reports
- [ ] Barcode scanning support

---

## 📄 License

This project is provided as-is for educational and commercial use.

---

## 👨‍💻 Development

### Coding Standards

- **C++ Standard:** C++17
- **Naming Convention:**
  - Classes: PascalCase (`Item`, `MainWindow`)
  - Functions: camelCase (`getName()`, `addItem()`)
  - Variables: camelCase (`name`, `price`)
  - Private members: camelCase with prefix (`m_name`, `m_price`) - optional

### Building for Release

```bash
cmake --build . --config Release
```

### Cleaning Build

```bash
# Windows
rmdir /S /Q build

# Linux/macOS
rm -rf build
```

---

## 🐛 Known Issues

- Item names with spaces are not currently supported in text file storage
- No input validation for negative prices
- No confirmation dialog for delete operation

---

## 📞 Support

For issues or questions:
1. Check the **Troubleshooting** section above
2. Verify your Qt installation path
3. Ensure all files are in correct folders
4. Delete build folder and reconfigure CMake

---

## 🎉 Version History

### v1.0.0 (Current)
- Initial release
- Basic CRUD operations
- Qt5 Widgets GUI
- Text file storage
- CMake build system

---

**Built with ❤️ using Qt5 and C++17**
