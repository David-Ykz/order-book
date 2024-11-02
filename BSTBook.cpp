#include "BSTBook.h"


void BSTBook::removeLimit(std::set<int>& tree, std::vector<Limit*>& map, int price) {
    delete map[price];
    map[price] = nullptr;
    std::set<int>::iterator it = tree.find(price);
    tree.erase(it, tree.end());
}

BSTBook::BSTBook(int priceRange) {
    priceRange++;
    this->bidsMap.assign(priceRange, nullptr);
    this->asksMap.assign(priceRange, nullptr);
} 

void BSTBook::insertOrder(std::set<int>& tree, std::vector<Limit*>& map, Order* order) {
    int price = order->getPrice();
    if (map[price] == nullptr) {
        tree.insert(price);
        Limit* limit = new Limit(price);
        limit->addOrder(order);
        map[price] = limit;
    } else {
        map[price]->addOrder(order);
    }
}

void BSTBook::executeTrade(int bidPrice, int askPrice) {
    Limit bid = *bidsMap[bidPrice];
    Limit ask = *asksMap[askPrice];

    while (!bid.getOrders().empty() && !ask.getOrders().empty()) {
        Order* earliestBid = bid.getOrders().front();
        Order* earliestAsk = ask.getOrders().front();
        int lowestVolume = std::min(earliestBid->getVolume(), earliestAsk->getVolume());
        earliestBid->removeVolume(lowestVolume);
        earliestAsk->removeVolume(lowestVolume);

        if (earliestBid->getVolume() == 0) {
            bid.getOrders().pop();
        }
        if (earliestAsk->getVolume() == 0) {
            ask.getOrders().pop();
        }
    }
    if (bid.getOrders().empty()) {
        removeLimit(bidsTree, bidsMap, bid.getPrice());
    }
    if (ask.getOrders().empty()) {
        removeLimit(asksTree, asksMap, ask.getPrice());
    }
}

void BSTBook::attemptMatch() {
    if (bidsTree.empty() || asksTree.empty()) {
        return;
    }
    int maxBidPrice = *bidsTree.rbegin();
    int minAskPrice = *asksTree.begin();

    if (maxBidPrice >= minAskPrice) {
        executeTrade(maxBidPrice, minAskPrice);
    }
}

void BSTBook::addToOrderbook(Order* order) {
    insertOrder(order->getIsBidOrAsk() ? bidsTree : asksTree, order->getIsBidOrAsk() ? bidsMap : asksMap, order);
    attemptMatch();
}

void BSTBook::printInfo() {
    std::cout << bidsTree.size() << " -- " << asksTree.size() << std::endl; 
}