#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "saleslogic.h"

// Forward declarations for Qt classes
QT_BEGIN_NAMESPACE
class QTableView;
class QStandardItemModel;
class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QHBoxLayout;
class QWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleAddItem();
    void handleDeleteItem();
    void handleSearchQuery(const QString &text);
    void refreshTableModel();

private:
    void setupUi();

    // Business logic handler
    SalesLogic m_salesLogic;

    // UI Elements
    QTableView *m_tableView;
    QStandardItemModel *m_model;
    QPushButton *m_addButton;
    QPushButton *m_deleteButton;
    QLineEdit *m_searchLineEdit;

    // Layouts
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_buttonLayout;
    QWidget *m_centralWidget;
};

#endif // MAINWINDOW_H
