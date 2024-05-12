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

void threadB() {
    mutex2.lock();
    std::cout << "Thread B acquired mutex2" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    mutex1.lock();
    std::cout << "Thread B acquired mutex1" << std::endl;
    mutex1.unlock();
    mutex2.unlock();
}

int main() {
    std::thread t1(threadA);
    std::thread t2(threadB);

    t1.join();
    t2.join();

    return 0;
}
