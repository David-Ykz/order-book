#include "order.h"
#include <queue>

class Limit {
public:
    queue<Order*> orders;

    Limit(Order* order) {
        orders.push(order);
    }
    
    int price() {
        if (orders.empty()) return -1;
        return orders.front()->price;
    }
};