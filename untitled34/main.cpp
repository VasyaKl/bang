#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

int counter = 0;
std::mutex counter_mutex;

int main() {
    std::vector<std::thread> threads;

    for (int i = 1; i <= 3; ++i) {
        threads.emplace_back([i]() {
            int squared = i * i;
            std::cout << "Thread " << i << ": " << squared << std::endl;

            counter_mutex.lock();
            counter += i;
            std::cout << "Counter: " << counter << std::endl;
            counter_mutex.unlock();
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
