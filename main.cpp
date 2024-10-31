#include <iostream>
#include "Limit.cpp"
#include <random>
#include <vector>
#include <algorithm>


int getRandomInteger(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

double getRandomDouble(double min, double max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(min, max);
    return dis(gen);
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
        newLimit.addOrder(order);
        book.push_back(newLimit);
    }
}

void executeTrade(std::vector<Limit>::iterator bidPointer, std::vector<Limit>::iterator askPointer) {
    Limit& bid = *bidPointer;
    Limit& ask = *askPointer;
    bool keepMatching = true;

    // std::cout << "executing trade dd";
    while (!bid.getOrders().empty() && !ask.getOrders().empty()) {
        Order earliestBid = bid.getOrders().front();
        Order earliestAsk = ask.getOrders().front();

        int lowestVolume = std::min(earliestBid.getVolume(), earliestAsk.getVolume());
        earliestBid.setVolume(earliestBid.getVolume() - lowestVolume);
        earliestAsk.setVolume(earliestAsk.getVolume() - lowestVolume);

        // earliestBid.printOrder();
        // earliestAsk.printOrder();


        if (earliestBid.getVolume() == 0) {
            bid.getOrders().pop();
        }
        if (earliestAsk.getVolume() == 0) {
            ask.getOrders().pop();
        }
    }
}


void attemptMatch(std::vector<Limit>& bids, std::vector<Limit>& asks) {
    if (bids.empty() || asks.empty()) {
        return;
    }
    auto maxBid = std::max_element(bids.begin(), bids.end(),
        [](Limit& a, Limit& b) {
            return a.getPrice() < b.getPrice();
        });
    auto minAsk = std::min_element(asks.begin(), asks.end(),
        [](Limit& a, Limit& b) {
            return a.getPrice() < b.getPrice();
        });
    if (maxBid->getPrice() >= minAsk->getPrice()) {
        executeTrade(maxBid, minAsk);
        if (maxBid->getOrders().empty()) {
            bids.erase(maxBid);
        }
        if (minAsk->getOrders().empty()) {
            asks.erase(minAsk);
        }
    }
}

void addToOrderbook(std::vector<Limit>& bids, std::vector<Limit>& asks, Order& order) {
    insertOrder(order.getIsBidOrAsk() ? bids : asks, order);
    attemptMatch(bids, asks);
}


void generateOrders(std::vector<Limit>& bidOrderbook, std::vector<Limit>& askOrderbook, int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        Order buyOrder = Order(1, i, 1);
        Order sellOrder = Order(1, i, 0);
        // buyOrder.printOrder();
        // sellOrder.printOrder();
        addToOrderbook(bidOrderbook, askOrderbook, buyOrder);
        addToOrderbook(bidOrderbook, askOrderbook, sellOrder);
    }

}

void generateRandomOrders(std::vector<Limit>& bidOrderbook, std::vector<Limit>& askOrderbook, int numOrders, int lowerPriceRange, int upperPriceRange) {
    for (int i = 0; i < numOrders; i++) {
        if (i % 100000 == 0) {
            // std::cout << i << " ";
        }
        Order order = Order(getRandomInteger(0, 10000), getRandomInteger(lowerPriceRange, upperPriceRange), i % 2);
        addToOrderbook(bidOrderbook, askOrderbook, order);
    }
}



int main() {
    for (int j = 0; j < 10; j++) {
    std::vector<Limit> bidOrderbook;
    std::vector<Limit> askOrderbook;

    // Order buyOrder = Order(1, 5, 1);
    // Order sellOrder = Order(2, 5, 0);
    // buyOrder.printOrder();
    // sellOrder.printOrder();
    // addToOrderbook(bidOrderbook, askOrderbook, buyOrder);
    // addToOrderbook(bidOrderbook, askOrderbook, sellOrder);
    auto start = std::chrono::high_resolution_clock::now();
    generateRandomOrders(bidOrderbook, askOrderbook, 10000, 0, 500);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    std::cout << "Time taken: " << duration.count()/1000.0 << " seconds" << std::endl;
    std::cout << duration.count()/1000.0 << std::endl;

    // 2 hr 30 min for 1 million records, 4 minutes for 100k records

    // std::cout << std::endl;
    // std::cout << bidOrderbook.size() << " -- " << askOrderbook.size() << std::endl;

    }
    return 0;
}