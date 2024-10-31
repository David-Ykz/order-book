#include "Order.h"

int Order::idCounter = 0;

int Order::getId() {
    return id;
}

int Order::getVolume() {
    return volume;
}

int Order::getPrice() {
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

void Order::setVolume(int volume) {
    this->volume = volume;
}

Order::Order(int volume, int price, bool bidOrAsk): 
    id(++idCounter), 
    volume(volume), 
    price(price), 
    bidOrAsk(bidOrAsk), 
    timestamp(std::chrono::high_resolution_clock::now()) {
}

void Order::printOrder() {
    std::cout << "id: " << id << " volume: " << volume << " price: " << price << " bidOrAsk: " << bidOrAsk << std::endl;
}
