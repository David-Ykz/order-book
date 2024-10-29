#ifndef ORDER_H
#define ORDER_H

#include <chrono>
#include <iostream>

class Order {
private:
    static int idCounter;
    const int id;
    int volume;
    const double price;
    const std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
    const bool bidOrAsk; // 1 for bid 0 for ask
    bool isValid;
public:
    Order(int volume, double price, bool bidOrAsk);
    int getId();
    int getVolume();
    double getPrice();
    std::chrono::time_point<std::chrono::high_resolution_clock> getTimestamp();
    bool getIsBidOrAsk();
    bool getIsValid();
    void printOrder();
};

#endif