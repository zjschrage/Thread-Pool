#include "threadpool.h"
#include <chrono>
#include <random>
#include <iostream>

ThreadPool::ThreadPool(int thds, int it) : max_threads(thds), total_iter(it) {
    running = true;
    current_iter = 0;
    pool = (Thread*) malloc(sizeof(Thread) * max_threads);
    avalability = (bool*) malloc(sizeof(bool) * max_threads);
    for (int i = 0; i < max_threads; i++) {
        free_indecies.push(i);
        avalability[i] = true;
    }
}

void ThreadPool::thread_pool_executor() {
    while (running) {
        while (free_indecies.size() > 0) {

            cout_lock.lock();
            std::cout << "Making Thread to do task near " << current_iter << std::endl;
            cout_lock.unlock();

            int i = free_indecies.front();
            pool[i] = std::make_unique<std::thread>(&ThreadPool::worker, this, &avalability[i]);
            free_indecies.pop();
            avalability[i] = false;
        }
        for (int i = 0; i < max_threads; i++) {
            if (avalability[i]) {
                pool[i]->join();
                current_iter++;
                free_indecies.push(i);

                cout_lock.lock();
                std::cout << "Free Index:" << i << std::endl;
                cout_lock.unlock();

                if (current_iter == total_iter) running = false;
            }
        }
    }
    for (int i = 0; i < max_threads; i++) {
        if (pool[i]->joinable()) {
            pool[i]->join();
        }
    }
}

void ThreadPool::worker(bool* complete) {
    double r = ((double) rand() / (RAND_MAX)) * 4;
    std::this_thread::sleep_for(std::chrono::seconds((int)(r+1)));
    *complete = true;
}