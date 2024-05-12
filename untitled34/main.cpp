#include <iostream>
#include <thread>
#include <vector>

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            int squared = i * i;
            std::cout << "Thread " << i << ": " << squared << std::endl;
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
