#ifndef ITEM_H
#define ITEM_H

#include <QString>

class Item {
public:
    Item() = default;
    Item(QString n, double p);

    QString getName() const { return name; }
    double getPrice() const { return price; }

private:
    QString name;
    double price;
};

#endif
