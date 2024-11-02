#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "BSTBook.cpp"

std::chrono::nanoseconds randomGenerationDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds timeTaken = std::chrono::nanoseconds(0);


int getRandomInteger(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);
    return dis(gen);
}

// void generateOrders(std::vector<Limit>& bidOrderbook, std::vector<Limit>& askOrderbook, int numOrders) {
//     for (int i = 0; i < numOrders; i++) {
//         Order buyOrder = Order(1, i, 1);
//         Order sellOrder = Order(1, i, 0);
//         // buyOrder.printOrder();
//         // sellOrder.printOrder();
//         addToOrderbook(bidOrderbook, askOrderbook, buyOrder);
//         addToOrderbook(bidOrderbook, askOrderbook, sellOrder);
//     }

// }

void generateRandomOrders(BSTBook& book, int numOrders, int lowerPriceRange, int upperPriceRange) {
    for (int i = 0; i < numOrders; i++) {
        Order order = Order(getRandomInteger(0, 10000), getRandomInteger(lowerPriceRange, upperPriceRange), i % 2);
        auto start = std::chrono::high_resolution_clock::now();
        book.addToOrderbook(order);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        timeTaken += duration;
    }
}


void speedBenchmark(BSTBook& book, int lowerPrice, int upperPrice, int numOrders) {
    for (int i = lowerPrice; i <= upperPrice; i++) {
        for (int j = 1; j <= numOrders; j++) {
            Order order = Order(j, i, 1);
            Order otherOrder = Order(j, i, 0);
            auto start = std::chrono::high_resolution_clock::now();
            book.addToOrderbook(order);
            book.addToOrderbook(otherOrder);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
            timeTaken += duration;
        }
    }
    // for (int i = upperPrice; i >= lowerPrice; i--) {
    //     for (int j = 1; j <= numOrders; j++) {
    //         Order order = Order(j, i, 0);
    //         auto start = std::chrono::high_resolution_clock::now();
    //         book.addToOrderbook(order);
    //         auto end = std::chrono::high_resolution_clock::now();
    //         auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    //         timeTaken += duration;
    //     }
    // }
}

int main() {
    // Order buyOrder = Order(1, 5, 1);
    // Order sellOrder = Order(1, 6, 0);
    // buyOrder.printOrder();
    // sellOrder.printOrder();
    // book.addToOrderbook(buyOrder);
    // book.addToOrderbook(sellOrder);
    // book.printInfo();
    auto start = std::chrono::high_resolution_clock::now();

    for (int j = 0; j < 1; j++) {
        BSTBook book = BSTBook();
//        generateRandomOrders(book, 1000000, 0, 500);
        speedBenchmark(book, 0, 10, 100000);
        book.printInfo();
    }

    // std::cout << "Total randtime: " << std::chrono::duration_cast<std::chrono::duration<double>>(randomGenerationDuration).count() << " seconds" << std::endl;
    // std::cout << "Total clocktime: " << std::chrono::duration_cast<std::chrono::duration<double>>(clockDuration).count() << " seconds" << std::endl;
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Average time taken: " << timeTaken.count()/1000000000.0 << " seconds" << std::endl;
    std::cout << "Average time taken: " << duration.count()/1000000000.0 << " seconds" << std::endl;

    return 0;
}