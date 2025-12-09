#include <gtest/gtest.h>
#include "Inventory.h"
#include "Item.h"

//
// Test 1: Check if adding items increases the total number of items
//
TEST(InventoryTest, AddItemIncreasesCount) {

    Inventory inv;
    // Create a new empty Inventory object called "inv"
    // This is like creating an empty list or empty bag

    auto before = inv.getItems();
    // Get all items currently in the inventory (should be empty)

    const auto initialCount = before.size();
    // Store how many items were there before adding (probably 0)

    // Add two new items to the inventory
    inv.addItem(Item("Pen", 10.0));
    inv.addItem(Item("Book", 50.0));

    auto after = inv.getItems();
    // Get the item list again after adding items

    // Check if the size increased by exactly 2
    EXPECT_EQ(after.size(), initialCount + 2);
}

//
// Test 2: Check if an added item stores the correct name and price
//
TEST(InventoryTest, AddedItemHasCorrectData) {

    Inventory inv;
    // Create a new empty inventory

    inv.addItem(Item("Keyboard", 75.0));
    // Add one item: Name = "Keyboard", Price = 75.0

    auto items = inv.getItems();
    // Get all items inside the inventory

    ASSERT_FALSE(items.empty());
    // The inventory should NOT be empty after adding the item

    const Item &last = items.back();
    // Get the last item (the item we just added)

    // Check if the stored name matches "Keyboard"
    EXPECT_EQ(last.getName(), "Keyboard");

    // Check if the stored price matches 75.0
    EXPECT_DOUBLE_EQ(last.getPrice(), 75.0);
}

//
// Test 3: Check if deleting an item actually removes one entry
//
TEST(InventoryTest, DeleteItemRemovesEntry) {

    Inventory inv;
    // New empty inventory

    // Add two items so we have something to delete
    inv.addItem(Item("Laptop", 999.0));
    inv.addItem(Item("Mouse", 25.0));

    auto before = inv.getItems();
    // Get items before deleting

    ASSERT_GE(before.size(), 2u);
    // Make sure we have at least 2 items

    inv.deleteItem(0);
    // Delete the item at index 0
    // (use 1 if your delete function uses 1-based index)

    auto after = inv.getItems();
    // Get items after deletion

    // Now size must be 1 less than before
    EXPECT_EQ(after.size(), before.size() - 1);
}

//
// Test 4: Same as the "AddedItemHasCorrectData" test but with different values
//
TEST(InventoryTest, New_Test1)
{
    Inventory inv;
    // Create empty inventory

    inv.addItem(Item("Pen", 11.0));
    // Add one item

    auto items = inv.getItems();
    // Get item list

    ASSERT_FALSE(items.empty());
    // Inventory must not be empty

    const Item &last = items.back();
    // Get last item added

    EXPECT_EQ(last.getName(), "Pen");
    // Check correct name

    EXPECT_DOUBLE_EQ(last.getPrice(), 11.0);
    // Check correct price
}

//
// Test 5: Add an item, verify it, then delete it, and verify size decreases
//
TEST(InventoryTest, New_Test2)
{
    Inventory inv;
    // New inventory

    inv.addItem(Item("Book", 4000.0));
    // Add one item with large price

    auto Before = inv.getItems();
    // Get item list before deletion

    ASSERT_FALSE(Before.empty());
    // Should not be empty

    const Item &last = Before.back();
    // Get added item

    EXPECT_EQ(last.getName(), "Book");
    // Check correct name

    EXPECT_DOUBLE_EQ(last.getPrice(), 4000.0);
    // Check correct price

    inv.deleteItem(0);
    // Delete the item at index 0

    auto After = inv.getItems();
    // Get list after deletion

    ASSERT_FALSE(After.empty() != Before.empty());
    // Optional sanity check (simple validation)

    EXPECT_EQ(After.size(), Before.size() - 1);
    // Size must decrease by exactly 1 after deletion
}
