#include <iostream>
#include "Limit.cpp"
#include <random>

// void generateRandomOrders(bool bidOrAsk)

void generateOrders(int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        Order buyOrder = Order(1, i, 1);
        Order sellOrder = Order(1, i, 0);
        buyOrder.printOrder();
        sellOrder.printOrder();
    }
}

void addToOrderbook( Order order) {

}



int main() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    srand(static_cast<unsigned int>(duration.count()));


    generateOrders(5);
    return 0;
}