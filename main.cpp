#include <iostream>
#include "graph.h"

int main() {
    std::unordered_map<int, int> map;
    try {
        map.at(5);
    }
    catch (std::exception& e){
        std::cout << e.what();
    }
    return 0;
}
