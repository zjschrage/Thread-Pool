#include "threadpool.h"
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

template<typename Func, typename... Args>
void ThreadPool::thread_pool_executor(Func func, Args... args) {
    while (running) {
        while (free_indecies.size() > 0 && running) {

            cout_lock.lock();
            std::cout << "Making Thread to do task " << (current_iter + 1) << std::endl;
            cout_lock.unlock();

            int i = free_indecies.front();
            pool[i] = std::make_unique<std::thread>(&ThreadPool::worker, this, &avalability[i], func, args...);
            free_indecies.pop();
            avalability[i] = false;
            current_iter++;
            if (current_iter == total_iter) running = false;
        }
        for (int i = 0; i < max_threads; i++) {
            if (avalability[i]) {
                pool[i]->join();
                free_indecies.push(i);
            }
        }
    }
    for (int i = 0; i < max_threads; i++) {
        if (pool[i]->joinable()) {
            // pool[i]->join(); // Why is this causing abort error I am checking joinable
        }
    }
}

template<typename Func, typename... Args>
void ThreadPool::worker(bool* complete, Func func, Args... args) {
    func(args...);
    *complete = true;
}