#ifndef BSTBook_H
#define BSTBook_H

#include <iostream>
#include <set>
#include <unordered_map>
#include <memory>
#include "Limit.cpp"

class BSTBook {
private:
    std::set<int> bidsTree;
    std::set<int> asksTree;
    std::unordered_map<int, std::unique_ptr<Limit>> bidsMap;
    std::unordered_map<int, std::unique_ptr<Limit>> asksMap;
    void removeLimit(std::set<int>& tree, std::unordered_map<int, std::unique_ptr<Limit>>& map, int price);

    static std::chrono::nanoseconds removeLimitDuration;
    static std::chrono::nanoseconds insertOrderDuration;
    static std::chrono::nanoseconds executeTradeDuration;
    static std::chrono::nanoseconds attemptMatchDuration;
    static std::chrono::nanoseconds addToOrderbookDuration;


public:
    BSTBook();
    void insertOrder(std::set<int>& tree, std::unordered_map<int, std::unique_ptr<Limit>>& map, Order& order);
    void executeTrade(int bidPrice, int askPrice);
    void attemptMatch();
    void addToOrderbook(Order& order);
    void printInfo();
};

#endif