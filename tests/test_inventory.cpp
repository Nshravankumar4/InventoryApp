#include <gtest/gtest.h>
#include "Inventory.h"
#include "Item.h"

TEST(InventoryTest, AddItemIncreasesCount) {
    Inventory inv;

    auto before = inv.getItems();
    const auto initialCount = before.size();

    inv.addItem(Item("Pen", 10.0));
    inv.addItem(Item("Book", 50.0));

    auto after = inv.getItems();
    EXPECT_EQ(after.size(), initialCount + 2);
}

TEST(InventoryTest, AddedItemHasCorrectData) {
    Inventory inv;

    inv.addItem(Item("Keyboard", 75.0));

    auto items = inv.getItems();
    ASSERT_FALSE(items.empty());

    const Item &last = items.back();
    EXPECT_EQ(last.getName(), "Keyboard");
    EXPECT_DOUBLE_EQ(last.getPrice(), 75.0);
}

TEST(InventoryTest, DeleteItemRemovesEntry) {
    Inventory inv;
    inv.addItem(Item("Laptop", 999.0));
    inv.addItem(Item("Mouse", 25.0));

    auto before = inv.getItems();
    ASSERT_GE(before.size(), 2u);

    inv.deleteItem(0);   // or 1 if 1-based

    auto after = inv.getItems();
    EXPECT_EQ(after.size(), before.size() - 1);
}
