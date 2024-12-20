#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "BSTBook.cpp"

std::chrono::nanoseconds timeTaken = std::chrono::nanoseconds(0);


int getRandomInteger(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

void generateRandomOrders(BSTBook& book, int numOrders, int lowerPriceRange, int upperPriceRange) {
    for (int i = 0; i < numOrders; i++) {
        Order* order = new Order(getRandomInteger(0, 10000), getRandomInteger(lowerPriceRange, upperPriceRange), i % 2);
        auto start = std::chrono::high_resolution_clock::now();
        book.addToOrderbook(order);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        timeTaken += duration;
    }
}

void generateOrders(BSTBook& book, int lowerPrice, int upperPrice, int numOrders) {
    for (int i = lowerPrice; i <= upperPrice; i++) {
        for (int j = 1; j <= numOrders; j++) {
            Order* order = new Order(j, i, 1);
            auto start = std::chrono::high_resolution_clock::now();
            book.addToOrderbook(order);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            timeTaken += duration;
        }
    }
    for (int i = lowerPrice; i <= upperPrice; i++) {
        for (int j = 1; j <= numOrders; j++) {
            Order* order = new Order(j, i, 0);
            auto start = std::chrono::high_resolution_clock::now();
            book.addToOrderbook(order);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            timeTaken += duration;
        }
    }
}

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < 1; j++) {
        int lowerPrice = 0;
        int upperPrice = 500;
        BSTBook book = BSTBook(upperPrice - lowerPrice);
//        generateOrders(book, lowerPrice, upperPrice, 1);
        generateOrders(book, lowerPrice, upperPrice, 125);
        book.printInfo();
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Real time taken: " << timeTaken.count()/2000000000.0 << " seconds" << std::endl;
    std::cout << "Total time taken: " << duration.count()/2000000000.0 << " seconds" << std::endl;

    return 0;
}