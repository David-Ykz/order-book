#ifndef LIMIT_H
#define LIMIT_H

#include <queue>
#include "Order.cpp"

class Limit {
private:
    int price;
    // TODO: change to std::queue<Order*>
    std::queue<Order*> orders;
    
public:
    Limit(int price);
    int getPrice();
    std::queue<Order*>* getOrders();
    void addOrder(Order* order);
    int totalVolume();
};

#endif