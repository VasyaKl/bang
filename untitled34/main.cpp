#include <iostream>
#include <thread>
#include <vector>

int counter = 0;

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            int squared = i * i;
            std::cout << "Thread " << i << ": " << squared << std::endl;
            counter += i;
            std::cout << "Counter: " << counter << std::endl;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
