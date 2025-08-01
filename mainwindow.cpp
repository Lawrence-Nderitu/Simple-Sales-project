#include "mainwindow.h"
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QHeaderView>
#include <QMessageBox>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_salesLogic("Items.csv") {
    setupUi();
    refreshTableModel(); // Initial data load
}

MainWindow::~MainWindow() {
    // Qt's parent-child mechanism handles deletion of UI elements
}

void MainWindow::setupUi() {
    // Main widget and layout
    m_centralWidget = new QWidget(this);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    // Search bar
    m_searchLineEdit = new QLineEdit(this);
    m_searchLineEdit->setPlaceholderText("Search by ID, Name, or Cost...");
    m_mainLayout->addWidget(m_searchLineEdit);

    // Table view for displaying items
    m_tableView = new QTableView(this);
    m_model = new QStandardItemModel(0, 3, this); // 0 rows, 3 columns
    m_model->setHorizontalHeaderLabels({"ID", "Item Name", "Cost"});
    m_tableView->setModel(m_model);
    m_tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_tableView->horizontalHeader()->setStretchLastSection(true);
    m_mainLayout->addWidget(m_tableView);

    // Button layout
    m_buttonLayout = new QHBoxLayout();
    m_addButton = new QPushButton("Add Item", this);
    m_deleteButton = new QPushButton("Delete Selected Item", this);
    m_buttonLayout->addWidget(m_addButton);
    m_buttonLayout->addWidget(m_deleteButton);
    m_mainLayout->addLayout(m_buttonLayout);

    // Set the central widget
    setCentralWidget(m_centralWidget);
    setWindowTitle("Nderitu's Store Management System");
    resize(600, 400); // Set a reasonable default size

    // Connect signals to slots
    connect(m_addButton, &QPushButton::clicked, this, &MainWindow::handleAddItem);
    connect(m_deleteButton, &QPushButton::clicked, this, &MainWindow::handleDeleteItem);
    connect(m_searchLineEdit, &QLineEdit::textChanged, this, &MainWindow::handleSearchQuery);
}

void MainWindow::refreshTableModel() {
    m_model->setRowCount(0); // Clear the table
    std::vector<Item> items = m_salesLogic.getAllItems();
    for (const auto& item : items) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(QString::number(item.id)));
        rowItems.append(new QStandardItem(QString::fromStdString(item.name)));
        rowItems.append(new QStandardItem(QString::number(item.cost, 'f', 2)));
        m_model->appendRow(rowItems);
    }
}

void MainWindow::handleAddItem() {
    bool ok;
    int id = QInputDialog::getInt(this, "Add Item", "Item ID:", 1, 0, 1000000, 1, &ok);
    if (!ok) return; // User cancelled

    // Check if ID already exists
    for (const auto& item : m_salesLogic.getAllItems()) {
        if (item.id == id) {
            QMessageBox::warning(this, "Error", "An item with this ID already exists.");
            return;
        }
    }

    QString name = QInputDialog::getText(this, "Add Item", "Item Name:", QLineEdit::Normal, "", &ok);
    if (!ok || name.isEmpty()) return;

    double cost = QInputDialog::getDouble(this, "Add Item", "Item Cost:", 0.0, 0, 10000000, 2, &ok);
    if (!ok) return;

    Item newItem = {id, name.toStdString(), cost};
    if (m_salesLogic.addItem(newItem)) {
        QMessageBox::information(this, "Success", "Item added successfully.");
        refreshTableModel();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add item to the file.");
    }
}

void MainWindow::handleDeleteItem() {
    QModelIndexList selectedRows = m_tableView->selectionModel()->selectedRows();
    if (selectedRows.isEmpty()) {
        QMessageBox::warning(this, "Selection Error", "Please select an item to delete.");
        return;
    }

    QModelIndex selectedIndex = selectedRows.first();
    int itemId = m_model->item(selectedIndex.row(), 0)->text().toInt();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirm Deletion", "Are you sure you want to delete this item?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (m_salesLogic.deleteItem(itemId)) {
            QMessageBox::information(this, "Success", "Item deleted successfully.");
            refreshTableModel();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete the item.");
        }
    }
}

void MainWindow::handleSearchQuery(const QString &text) {
    std::vector<Item> items = m_salesLogic.searchItems(text.toStdString());
    m_model->setRowCount(0); // Clear the table
    for (const auto& item : items) {
        QList<QStandardItem *> rowItems;
        rowItems.append(new QStandardItem(QString::number(item.id)));
        rowItems.append(new QStandardItem(QString::fromStdString(item.name)));
        rowItems.append(new QStandardItem(QString::number(item.cost, 'f', 2)));
        m_model->appendRow(rowItems);
    }
}
