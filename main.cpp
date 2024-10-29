#include <iostream>
#include "Limit.cpp"
#include <random>
#include <vector>
#include <algorithm>

// void generateRandomOrders(bool bidOrAsk)

void generateOrders(int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        Order buyOrder = Order(1, i, 1);
        Order sellOrder = Order(1, i, 0);
        buyOrder.printOrder();
        sellOrder.printOrder();
    }
}

void insertOrder(std::vector<Limit>& book, Order& order) {
    bool alreadyExists = false;
    for (Limit limit : book) {
        if (limit.getPrice() == order.getPrice()) {
            limit.addOrder(order);
            alreadyExists = true;
        }
    }
    if (!alreadyExists) {
        Limit newLimit = Limit(order.getPrice());
        book.push_back(newLimit);
    }
}

void addToOrderbook(std::vector<Limit>& bids, std::vector<Limit>& asks, Order& order) {
    insertOrder(order.getIsBidOrAsk() ? bids : asks, order);
    
}

void attemptMatch(std::vector<Limit>& bids, std::vector<Limit>& asks) {
    auto maxBid = std::max_element(bids.begin(), bids.end(),
        [](Order& a, Order& b) {
            return a.getPrice() < b.getPrice();
        });
    auto minAsk = std::min_element(asks.begin(), asks.end(),
        [](Order& a, Order& b) {
            return a.getPrice() < b.getPrice();
        });

    if (maxBid->getPrice() >= minAsk->getPrice()) {
        executeTrade(maxBid, minAsk);
    }
}

void executeTrade(std::vector<Limit>::iterator bidPointer, std::vector<Limit>::iterator askPointer) {
    Limit& bid = *bidPointer;
    Limit& ask = *askPointer;

    
    

}

// bid: 4, 6, 8, 10
// ask: 6, 7, 9, 19


int main() {
    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    srand(static_cast<unsigned int>(duration.count()));


    std::vector<Limit> bidOrderbook;
    std::vector<Limit> askOrderbook;



    generateOrders(5);
    return 0;
}