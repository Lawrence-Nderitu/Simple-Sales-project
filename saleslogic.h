#ifndef SALESLOGIC_H
#define SALESLOGIC_H

#include <vector>
#include <string>

// A simple struct to hold item data
struct Item {
    int id;
    std::string name;
    double cost;
};

class SalesLogic {
public:
    SalesLogic(const std::string& filename = "Items.csv");

    std::vector<Item> getAllItems();
    bool addItem(const Item& newItem);
    bool deleteItem(int itemId);
    std::vector<Item> searchItems(const std::string& searchTerm);

private:
    std::string m_filename;
    std::vector<Item> readItems();
    bool writeItems(const std::vector<Item>& items);
};

#endif // SALESLOGIC_H
