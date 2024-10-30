#ifndef LIMIT_H
#define LIMIT_H

#include <queue>
#include "Order.cpp"

class Limit {
private:
    double price;
    std::queue<Order> orders;
    
public:
    Limit(double price);
    double getPrice();
    std::queue<Order>& getOrders();
    void addOrder(Order& order);
};

#endif