#include <iostream>
#include <thread>
#include <mutex>

std::mutex mutex1, mutex2;

void threadA() {
    mutex1.lock();
    std::cout << "Thread A acquired mutex1" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex2.lock();
    std::cout << "Thread A acquired mutex2" << std::endl;
    mutex2.unlock();
    mutex1.unlock();
}
