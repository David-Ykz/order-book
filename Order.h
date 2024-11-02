#ifndef ORDER_H
#define ORDER_H

#include <chrono>
#include <iostream>

class Order {
private:
    static int idCounter;
    int id;
    int volume;
    int price;
    std::chrono::time_point<std::chrono::high_resolution_clock> timestamp;
    bool bidOrAsk; // 1 for bid 0 for ask
    bool isValid;
public:
    Order(int volume, int price, bool bidOrAsk);
    int getId();
    int getVolume();
    int getPrice();
    bool getIsBidOrAsk();
    bool getIsValid();
    void setVolume(int volume);
    void removeVolume(int volume);
    void printOrder();
};

#endif