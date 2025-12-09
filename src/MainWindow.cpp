#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QInputDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    updateInventoryList();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateInventoryList()
{
    ui->listWidget->clear();
    auto items = inventory.getItems();
    for (int i = 0; i < items.size(); ++i) {
        QString text = QString("%1. %2 | Price: %3")
        .arg(i+1)
            .arg(items[i].getName())
            .arg(items[i].getPrice());
        ui->listWidget->addItem(text);
    }
}

void MainWindow::on_addButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Item", "Item Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    double price = QInputDialog::getDouble(this, "Add Item", "Item Price:", 0, 0, 1000000, 2, &ok);
    if (!ok) return;

    inventory.addItem(Item(name, price));
    updateInventoryList();
}

void MainWindow::on_viewButton_clicked()
{
    updateInventoryList();
}

void MainWindow::on_deleteButton_clicked()
{
    bool ok;
    int index = QInputDialog::getInt(this, "Delete Item", "Item Number to Delete:", 1, 1, inventory.getItems().size(), 1, &ok);
    if (!ok) return;

    inventory.deleteItem(index-1);
    updateInventoryList();
}
