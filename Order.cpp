#include "Order.h"

int Order::idCounter = 0;

int Order::getId() {
    return id;
}

int Order::getVolume() {
    return volume;
}

double Order::getPrice() {
    return price;
}

std::chrono::time_point<std::chrono::high_resolution_clock> Order::getTimestamp() {
    return timestamp;
}

bool Order::getIsBidOrAsk() {
    return bidOrAsk;
}

bool Order::getIsValid() {
    return isValid;
}

Order::Order(int volume, double price, bool bidOrAsk): 
    id(++idCounter), 
    volume(volume), 
    price(price), 
    bidOrAsk(bidOrAsk), 
    timestamp(std::chrono::high_resolution_clock::now()) {
}

void Order::printOrder() {
    std::cout << "id: " << id << " volume: " << volume << " price: " << price << " bidOrAsk: " << bidOrAsk << std::endl;
}
