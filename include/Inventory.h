#ifndef INVENTORY_H
#define INVENTORY_H

#include "Item.h"
#include <QVector>

class Inventory {
public:
    Inventory();

    void loadItems();
    void saveItems();
    void addItem(const Item &item);
    void deleteItem(int index);
    QVector<Item> getItems() const;

private:
    QVector<Item> items;
};

#endif
