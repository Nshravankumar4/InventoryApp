#include <gtest/gtest.h>
#include "Item.h"

TEST(ItemTest, ConstructorSetsFields) {
    Item item("Pen", 10.0);

    EXPECT_EQ(item.getName(), "Pen");
    EXPECT_DOUBLE_EQ(item.getPrice(), 10.0);
}

// No InventoryTest tests in this file.
