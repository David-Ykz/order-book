#include "limit.h"
#include <set>
#include <unordered_map>

struct CompareMin {
    bool operator()(Limit* a, Limit* b) const {
        return a->price() < b->price();
    }
};

struct CompareMax {
    bool operator()(Limit* a, Limit* b) const {
        return a->price() > b->price();
    }
};

class Book {
public:
    set<Limit*, CompareMax> bidBook;
    set<Limit*, CompareMin> askBook;
    unordered_map<int, Limit*> bidPrices;
    unordered_map<int, Limit*> askPrices;
    unordered_map<int64_t, Order*> orders;
    vector<int64_t> processedOrders;

    Book() {}

    int getBidPrice() {
        while (!bidBook.empty()) {
            int price = (*bidBook.begin())->price();
            if (price > 0) {
                return price;
            } else {
                bidBook.erase(bidBook.begin());
            }
        }
        return -1;
    }

    int getAskPrice() {
        while (!askBook.empty()) {
            int price = (*askBook.begin())->price();
            if (price > 0) {
                return price;
            } else {
                askBook.erase(askBook.begin());
            }
        }
        return -1;
    }

    int64_t addBid(int volume, int price) {
        Order* order = new Order(volume, price);
        int64_t orderId = order->id;
        orders[orderId] = order;
        if (bidPrices.find(price) != bidPrices.end()) {
            bidPrices[price]->orders.push(order);
        } else {
            Limit* limit = new Limit(order);
            bidBook.insert(limit);
            bidPrices[price] = limit;
        }
        reconcile();
        return orderId;
    }

    int64_t addAsk(int volume, int price) {
        Order* order = new Order(volume, price);
        int64_t orderId = order->id;
        orders[orderId] = order;
        if (askPrices.find(price) != askPrices.end()) {
            askPrices[price]->orders.push(order);
        } else {
            Limit* limit = new Limit(order);
            askBook.insert(limit);
            askPrices[price] = limit;
        }
        reconcile();
        return orderId;
    }

    void reconcile() {
        if (bidBook.empty() || askBook.empty()) return;

        processedOrders.clear();
        while (getBidPrice() > 0 && getAskPrice() > 0 && getBidPrice() >= getAskPrice()) {
            Limit* bidLimit = (*bidBook.begin());
            Limit* askLimit = (*askBook.begin());
            while (!bidLimit->orders.empty() && !askLimit->orders.empty()) {
                Order* bidOrder = bidLimit->orders.front();
                Order* askOrder = askLimit->orders.front();

                if (bidOrder->volume > askOrder->volume) {
                    bidOrder->volume -= askOrder->volume;
                    askLimit->orders.pop();
                    processedOrders.push_back(askOrder->id);
                } else if (bidOrder->volume < askOrder->volume) {
                    askOrder->volume -= bidOrder->volume;
                    bidLimit->orders.pop();
                    processedOrders.push_back(bidOrder->id);
                } else {
                    askLimit->orders.pop();
                    processedOrders.push_back(askOrder->id);

                    bidLimit->orders.pop();
                    processedOrders.push_back(bidOrder->id);
                }
            }
        }
    }

    void cleanup() {
        for (auto& [price, limit] : bidPrices) {
            delete limit;
        }
        bidPrices.clear();

        for (auto& [price, limit] : askPrices) {
            delete limit;
        }
        askPrices.clear();

        for (auto& [orderId, order] : orders) {
            delete order;
        }
        orders.clear();
    }

};
