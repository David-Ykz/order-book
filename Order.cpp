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

bool Order::getIsBidOrAsk() {
    return bidOrAsk;
}

bool Order::getIsValid() {
    return isValid;
}

void Order::setVolume(int volume) {
    this->volume = volume;
}

void Order::removeVolume(int volume) {
    this->volume -= volume;
}

Order::Order(int volume, int price, bool bidOrAsk): 
    id(++idCounter), 
    volume(volume), 
    price(price), 
    bidOrAsk(bidOrAsk) {
}

void Order::printOrder() {
    std::cout << "id: " << id << " volume: " << volume << " price: " << price << " bidOrAsk: " << bidOrAsk << std::endl;
}
