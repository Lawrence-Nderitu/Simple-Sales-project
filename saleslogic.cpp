#include "saleslogic.h"
#include <fstream>
#include <sstream>
#include <algorithm>

SalesLogic::SalesLogic(const std::string& filename) : m_filename(filename) {
    // Ensure the file exists
    std::ofstream ofs(m_filename, std::ios::app);
}

std::vector<Item> SalesLogic::readItems() {
    std::vector<Item> items;
    std::ifstream file(m_filename);
    std::string line;

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string field;
        Item item;

        // Read ID
        if (getline(ss, field, ',')) {
            try {
                item.id = std::stoi(field);
            } catch (const std::invalid_argument& e) {
                continue; // Skip malformed lines
            }
        } else {
            continue;
        }

        // Read Name
        if (getline(ss, field, ',')) {
            item.name = field;
        } else {
            continue;
        }

        // Read Cost
        if (getline(ss, field, ',')) {
            try {
                item.cost = std::stod(field);
            } catch (const std::invalid_argument& e) {
                continue; // Skip malformed lines
            }
        } else {
            continue;
        }

        items.push_back(item);
    }
    return items;
}

bool SalesLogic::writeItems(const std::vector<Item>& items) {
    std::ofstream file(m_filename, std::ios::trunc); // Overwrite the file
    if (!file.is_open()) {
        return false;
    }

    for (const auto& item : items) {
        file << item.id << "," << item.name << "," << item.cost << "\n";
    }
    return true;
}

std::vector<Item> SalesLogic::getAllItems() {
    return readItems();
}

bool SalesLogic::addItem(const Item& newItem) {
    std::vector<Item> items = readItems();

    // Check for duplicate ID
    for (const auto& item : items) {
        if (item.id == newItem.id) {
            return false; // ID already exists
        }
    }

    items.push_back(newItem);
    return writeItems(items);
}

bool SalesLogic::deleteItem(int itemId) {
    std::vector<Item> items = readItems();
    auto it = std::remove_if(items.begin(), items.end(), [itemId](const Item& item) {
        return item.id == itemId;
    });

    if (it != items.end()) {
        items.erase(it, items.end());
        return writeItems(items);
    }
    return false; // Item not found
}

std::vector<Item> SalesLogic::searchItems(const std::string& searchTerm) {
    std::vector<Item> items = readItems();
    std::vector<Item> results;

    if (searchTerm.empty()) {
        return items;
    }

    std::string lowerSearchTerm = searchTerm;
    std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);

    for (const auto& item : items) {
        std::string lowerItemName = item.name;
        std::transform(lowerItemName.begin(), lowerItemName.end(), lowerItemName.begin(), ::tolower);

        // Search by name, ID, or cost
        if (lowerItemName.find(lowerSearchTerm) != std::string::npos ||
            std::to_string(item.id).find(searchTerm) != std::string::npos ||
            std::to_string(item.cost).find(searchTerm) != std::string::npos) {
            results.push_back(item);
        }
    }
    return results;
}
