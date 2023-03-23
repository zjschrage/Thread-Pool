#include "threadpool.h"
#include <iostream>

int my_important_work = 0;
std::mutex my_lock;

void worker(...) {
    double r = ((double) rand() / (RAND_MAX)) * 2;
    std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));

    const std::lock_guard<std::mutex> lock(my_lock);
    std::cout << "Working " << (my_important_work + 1) << std::endl;
    my_important_work++;
}

void worker2(int a, int b, char c) {
    double r = ((double) rand() / (RAND_MAX)) * 2;
    std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));

    const std::lock_guard<std::mutex> lock(my_lock);
    std::cout << "Working 2 and here are my arguments " << a << " " << b << " " << c << std::endl;
    my_important_work++;
}

int main() {
    ThreadPool pool(15, 50);
    pool.thread_pool_executor(0, worker);
    //pool.thread_pool_executor(3, worker2, 1, 2, 'c'); //Not sure how to make this general for all functions
    std::cout << my_important_work << std::endl;
}
