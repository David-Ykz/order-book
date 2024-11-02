#include "BSTBook.h"

std::chrono::nanoseconds BSTBook::removeLimitDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds BSTBook::insertOrderDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds BSTBook::executeTradeDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds BSTBook::attemptMatchDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds BSTBook::addToOrderbookDuration = std::chrono::nanoseconds(0);


void BSTBook::removeLimit(std::set<int>& tree, std::unordered_map<int, Limit*>& map, int price) {
    auto start = std::chrono::high_resolution_clock::now();
    delete map[price];
    map.erase(map.find(price));
    std::set<int>::iterator it = tree.find(price);
    tree.erase(it, tree.end());
     auto end = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
     removeLimitDuration += duration;
}

BSTBook::BSTBook() {} 

void BSTBook::insertOrder(std::set<int>& tree, std::unordered_map<int, Limit*>& map, Order& order) {
    using Clock = std::chrono::high_resolution_clock;
    auto start = Clock::now();
    int price = order.getPrice();
    auto beforeFind = Clock::now();
    if (map.find(price) == map.end()) {
        auto beforeInsert = Clock::now();
        tree.insert(price);
        auto beforeLimit = Clock::now();
        Limit* limit = new Limit(price);
        limit->addOrder(order);
        auto beforeMap = Clock::now();
        map[price] = limit;

        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(beforeInsert - beforeFind).count() << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(beforeLimit - beforeInsert).count() << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(beforeMap - beforeLimit).count() << std::endl;
        std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(Clock::now() - beforeMap).count() << std::endl;

    } else {
        map[price]->addOrder(order);
    }
    auto end = std::chrono::high_resolution_clock::now();


    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    insertOrderDuration += duration;
}

void BSTBook::executeTrade(int bidPrice, int askPrice) {
    auto start = std::chrono::high_resolution_clock::now();
    Limit bid = *bidsMap[bidPrice];
    Limit ask = *asksMap[askPrice];

    while (!bid.getOrders().empty() && !ask.getOrders().empty()) {
        Order earliestBid = bid.getOrders().front();
        Order earliestAsk = ask.getOrders().front();
        int lowestVolume = std::min(earliestBid.getVolume(), earliestAsk.getVolume());
        earliestBid.setVolume(earliestBid.getVolume() - lowestVolume);
        earliestAsk.setVolume(earliestAsk.getVolume() - lowestVolume);

        if (earliestBid.getVolume() == 0) {
            bid.getOrders().pop();
        }
        if (earliestAsk.getVolume() == 0) {
            ask.getOrders().pop();
        }
    }
    if (bid.getOrders().empty()) {
        removeLimit(bidsTree, bidsMap, bid.getPrice());
    }
    if (ask.getOrders().empty()) {
        removeLimit(asksTree, asksMap, ask.getPrice());
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    insertOrderDuration += duration;
}

void BSTBook::attemptMatch() {
    auto start = std::chrono::high_resolution_clock::now();
    if (bidsTree.empty() || asksTree.empty()) {
        return;
    }
    int maxBidPrice = *bidsTree.rbegin();
    int minAskPrice = *asksTree.begin();


    if (maxBidPrice >= minAskPrice) {
        executeTrade(maxBidPrice, minAskPrice);
    }
     auto end = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
     attemptMatchDuration += duration;
}

void BSTBook::addToOrderbook(Order& order) {
    auto start = std::chrono::high_resolution_clock::now();
    insertOrder(order.getIsBidOrAsk() ? bidsTree : asksTree, order.getIsBidOrAsk() ? bidsMap : asksMap, order);
    attemptMatch();
     auto end = std::chrono::high_resolution_clock::now();
     auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
     addToOrderbookDuration += duration;
}

void BSTBook::printInfo() {
    std::cout << bidsTree.size() << " -- " << asksTree.size() << std::endl; 
    std::cout << insertOrderDuration.count() << " nanoseconds";



// std::cout << "Durations (in seconds):" << std::endl;
// std::cout << "Remove Limit Duration: " 
//           << std::chrono::duration_cast<std::chrono::duration<double>>(removeLimitDuration).count() << " seconds" << std::endl;
// std::cout << "Insert Order Duration: " 
//           << std::chrono::duration_cast<std::chrono::duration<double>>(insertOrderDuration).count() << " seconds" << std::endl;
// std::cout << "Execute Trade Duration: " 
//           << std::chrono::duration_cast<std::chrono::duration<double>>(executeTradeDuration).count() << " seconds" << std::endl;
// std::cout << "Attempt Match Duration: " 
//           << std::chrono::duration_cast<std::chrono::duration<double>>(attemptMatchDuration).count() << " seconds" << std::endl;
// std::cout << "Add To Orderbook Duration: " 
//           << std::chrono::duration_cast<std::chrono::duration<double>>(addToOrderbookDuration).count() << " seconds" << std::endl;
          }