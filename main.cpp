#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "BSTBook.cpp"

std::chrono::nanoseconds randomGenerationDuration = std::chrono::nanoseconds(0);
std::chrono::nanoseconds clockDuration = std::chrono::nanoseconds(0);


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
        if (i % 100000 == 0) {
            // std::cout << i << " ";
        }
        auto start = std::chrono::high_resolution_clock::now();

        Order order = Order(getRandomInteger(0, 10000), getRandomInteger(lowerPriceRange, upperPriceRange), i % 2);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        randomGenerationDuration += duration;
        start = std::chrono::high_resolution_clock::now();
        book.addToOrderbook(order);
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        clockDuration += duration;
    }
}



int main() {
    // Order buyOrder = Order(1, 5, 1);
    // Order sellOrder = Order(1, 6, 0);
    // buyOrder.printOrder();
    // sellOrder.printOrder();
    // book.addToOrderbook(buyOrder);
    // book.addToOrderbook(sellOrder);
    // book.printInfo();

    for (int j = 0; j < 10; j++) {
    BSTBook book = BSTBook();
    // std::vector<Limit> bidOrderbook;
    // std::vector<Limit> askOrderbook;

//     // std::priority_queue<Limit, std::vector<Limit>, MaxPriceComparator> bids;
//     // std::priority_queue<Limit, std::vector<Limit>, MinPriceComparator> asks;

    auto start = std::chrono::high_resolution_clock::now();
    // for (int i = 0; i < 1000000000; i++) {

    // }
    generateRandomOrders(book, 100000, 0, 500);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Total time taken: " << clockDuration.count()/((j + 1) * 1000000000.0) << " seconds" << std::endl;
    book.printInfo();
//    std::cout << duration.count()/1000.0 << std::endl;

//     // 2 hr 30 min for 1 million records, 4 minutes for 100k records

//     std::cout << std::endl;
    // book.printInfo();
    }

    std::cout << "Total randtime: " << std::chrono::duration_cast<std::chrono::duration<double>>(randomGenerationDuration).count() << " seconds" << std::endl;
    std::cout << "Total clocktime: " << std::chrono::duration_cast<std::chrono::duration<double>>(clockDuration).count() << " seconds" << std::endl;

    return 0;
}