#include <iostream>
#include <random>

std::string gene(const int length, std::mt19937 &rand) {
    std::string res;
    auto dist = std::uniform_int_distribution<char>('a', 'z');
    for (int i = 0; i < length; i++) 
        res += dist(rand);
    return res;
}

int main() {
    std::mt19937 rand(1234321);
    const int n = 100000;
    std::cout << n << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << gene(4, rand) << " "; 
    std::cout << std::endl;
    for (int i = 0; i < n; i++) {
        auto dist =
            std::uniform_int_distribution<int>(0, 10000000);
        std::cout << dist(rand) << " ";
    }
    std::cout << std::endl;
    int s = 16;
    std::cout << s << std::endl;
    for (int i = 0; i < s; i++) {

        auto dist =
            std::uniform_int_distribution<int>(0, n - 1);
        auto from = dist(rand);
        auto to = dist(rand);
        if (from > to) std::swap(from, to);
        std::cout << from << " " << to << " "
                  << gene(100000, rand) << std::endl;
    }
    return EXIT_SUCCESS;
}
