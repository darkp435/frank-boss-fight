// Debug functions such as print, error to avoid cluttering main file
#include <iostream>
namespace Debug {
    template<typename T> inline void print(T data) {
        std::cout << data << "\n";
    }

    template<typename T> inline void error(T data) {
        std::cerr << data << "\n";
    }
};