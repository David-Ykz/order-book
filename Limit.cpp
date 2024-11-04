#include "Limit.h"

int Limit::getPrice() {
    return price;
}

std::queue<Order*>* Limit::getOrders() {
    return &orders;
}

Limit::Limit(int price) : price(price) {};

void Limit::addOrder(Order* order) {
    orders.push(order);
}

int Limit::totalVolume() {
    int counter = 0;
    std::queue<Order*> tempQueue = orders;
    while (!tempQueue.empty()) {
        counter += tempQueue.front()->getVolume();
        tempQueue.pop();
    }
    return counter;
}