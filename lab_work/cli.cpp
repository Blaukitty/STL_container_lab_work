#include <iostream>
#include "Circle_list.hpp"

int main() {
    Circle_list<int> list = {1, 2, 3, 4, 5};

    for (const auto& x : list) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    return 0;
}
