void insertOrder(std::vector<Limit>& book, Order& order) {
    bool alreadyExists = false;
    for (Limit limit : book) {
        if (limit.getPrice() == order.getPrice()) {
            limit.addOrder(order);
            alreadyExists = true;
        }
    }
    if (!alreadyExists) {
        Limit newLimit = Limit(order.getPrice());
        newLimit.addOrder(order);
        book.push_back(newLimit);
    }
}

void executeTrade(std::vector<Limit>::iterator bidPointer, std::vector<Limit>::iterator askPointer) {
    Limit& bid = *bidPointer;
    Limit& ask = *askPointer;
    bool keepMatching = true;

    // std::cout << "executing trade dd";
    while (!bid.getOrders().empty() && !ask.getOrders().empty()) {
        Order earliestBid = bid.getOrders().front();
        Order earliestAsk = ask.getOrders().front();

        int lowestVolume = std::min(earliestBid.getVolume(), earliestAsk.getVolume());
        earliestBid.setVolume(earliestBid.getVolume() - lowestVolume);
        earliestAsk.setVolume(earliestAsk.getVolume() - lowestVolume);

        // earliestBid.printOrder();
        // earliestAsk.printOrder();


        if (earliestBid.getVolume() == 0) {
            bid.getOrders().pop();
        }
        if (earliestAsk.getVolume() == 0) {
            ask.getOrders().pop();
        }
    }
}


void attemptMatch(std::vector<Limit>& bids, std::vector<Limit>& asks) {
    if (bids.empty() || asks.empty()) {
        return;
    }
    auto maxBid = std::max_element(bids.begin(), bids.end(),
        [](Limit& a, Limit& b) {
            return a.getPrice() < b.getPrice();
        });
    auto minAsk = std::min_element(asks.begin(), asks.end(),
        [](Limit& a, Limit& b) {
            return a.getPrice() < b.getPrice();
        });
    if (maxBid->getPrice() >= minAsk->getPrice()) {
        executeTrade(maxBid, minAsk);
        if (maxBid->getOrders().empty()) {
            bids.erase(maxBid);
        }
        if (minAsk->getOrders().empty()) {
            asks.erase(minAsk);
        }
    }
}

void addToOrderbook(std::vector<Limit>& bids, std::vector<Limit>& asks, Order& order) {
    insertOrder(order.getIsBidOrAsk() ? bids : asks, order);
    attemptMatch(bids, asks);
}


void generateOrders(std::vector<Limit>& bidOrderbook, std::vector<Limit>& askOrderbook, int numOrders) {
    for (int i = 0; i < numOrders; i++) {
        Order buyOrder = Order(1, i, 1);
        Order sellOrder = Order(1, i, 0);
        // buyOrder.printOrder();
        // sellOrder.printOrder();
        addToOrderbook(bidOrderbook, askOrderbook, buyOrder);
        addToOrderbook(bidOrderbook, askOrderbook, sellOrder);
    }

}

void generateRandomOrders(std::vector<Limit>& bidOrderbook, std::vector<Limit>& askOrderbook, int numOrders, int lowerPriceRange, int upperPriceRange) {
    for (int i = 0; i < numOrders; i++) {
        if (i % 100000 == 0) {
            // std::cout << i << " ";
        }
        Order order = Order(getRandomInteger(0, 10000), getRandomInteger(lowerPriceRange, upperPriceRange), i % 2);
        addToOrderbook(bidOrderbook, askOrderbook, order);
    }
}
