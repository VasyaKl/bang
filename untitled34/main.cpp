#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mutex_;
std::condition_variable cond_var_;
std::queue<int> queue_;
const int MAX_SIZE = 10;

void producer() {
    for (int i = 1; i <= 20; ++i) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [&]() { return queue_.size() < MAX_SIZE; });
        queue_.push(i);
        std::cout << "Produced: " << i << std::endl;
        lock.unlock();
        cond_var_.notify_one();
    }
}

void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_var_.wait(lock, [&]() { return !queue_.empty(); });
        int value = queue_.front();
        queue_.pop();
        std::cout << "Consumed: " << value << std::endl;
        lock.unlock();
        cond_var_.notify_one();
    }
}

int main() {
    std::thread prod(producer);
    std::thread cons(consumer);

    prod.join();
    cons.join();

    return 0;
}