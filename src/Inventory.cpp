#include "Inventory.h"
#include <fstream>
#include <string>

Inventory::Inventory() {
    loadItems();
}

void Inventory::loadItems() {
    items.clear();
    std::ifstream file("inventory.txt");
    std::string name;
    double price;

    while (file >> name >> price) {
        items.push_back(Item(QString::fromStdString(name), price));
    }
}

void Inventory::saveItems() {
    std::ofstream file("inventory.txt");
    for (const auto &item : items) {
        file << item.getName().toStdString() << " "
             << item.getPrice() << "\n";
    }
}

void Inventory::addItem(const Item &item) {
    items.push_back(item);
    saveItems();
}

void Inventory::deleteItem(int index) {
    if (index >= 0 && index < items.size()) {
        items.erase(items.begin() + index);
        saveItems();
    }
}

QVector<Item> Inventory::getItems() const {
    return items;
}
