#pragma once
#include <iostream>
#include <mutex>
#include <thread>

void worker();
void worker2(int a, int b, char c);
void worker3_slow(int x);

int my_important_work = 0;
std::mutex my_lock;

void worker() {
    // double r = ((double) rand() / (RAND_MAX)) * 2;
    // std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));

    const std::lock_guard<std::mutex> lock(my_lock);
    std::cout << "Working " << (my_important_work + 1) << std::endl;
    my_important_work++;
}

void worker2(int a, int b, char c) {
    // double r = ((double) rand() / (RAND_MAX)) * 2;
    // std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));

    const std::lock_guard<std::mutex> lock(my_lock);
    std::cout << "Working 2 (" << (my_important_work + 1) << ") and here are my arguments " << a << " " << b << " " << c << std::endl;
    my_important_work++;
}

void worker3_slow(int x) {
    double r = ((double) rand() / (RAND_MAX)) * 2;
    std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));

    const std::lock_guard<std::mutex> lock(my_lock);
    std::cout << "Working 3 with arg: " << x << std::endl;
    my_important_work++;
}