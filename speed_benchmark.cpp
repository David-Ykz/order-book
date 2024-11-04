#include "BSTBook.cpp"

int main() {
    BSTBook book = BSTBook();
    Order order = Order(1, 1, 1);
    book.addToOrderbook(order);

    book.printInfo();
    
    return 0;
}