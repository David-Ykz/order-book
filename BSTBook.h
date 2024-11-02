#ifndef BSTBook_H
#define BSTBook_H

#include <iostream>
#include <set>
#include <unordered_map>
#include <memory>
#include <vector>
#include "Limit.cpp"

class BSTBook {
private:
    std::set<int> bidsTree;
    std::set<int> asksTree;
    std::vector<Limit*> bidsMap;
    std::vector<Limit*> asksMap;
    void removeLimit(std::set<int>& tree, std::vector<Limit*>& map, int price);
public:
    BSTBook(int priceRange);
    void insertOrder(std::set<int>& tree, std::vector<Limit*>& map, Order* order);
    void executeTrade(int bidPrice, int askPrice);
    void attemptMatch();
    void addToOrderbook(Order* order);
    void printInfo();
};

#endif