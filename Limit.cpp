#include "Limit.h"

double Limit::getPrice() {
    return price;
}

std::queue<Order> Limit::getOrders() {
    return orders;
}

Limit::Limit(double price) : price(price) {};