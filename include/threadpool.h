#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include <stdarg.h>
#include <iostream>

typedef std::unique_ptr<std::thread> Thread;

class ThreadPool {
private:
    Thread* pool;
    bool* avalability;
    std::queue<int> free_indecies;
    bool running;
    int max_threads;
    int total_iter;
    int current_iter;
    template<typename Func, typename... Args> 
    void worker(bool* complete, Func func, Args... args);
    void reset();
public:
    ThreadPool(int thds, int it);
    ~ThreadPool();
    template<typename Func, typename... Args> 
    void thread_pool_executor(Func func, Args... args);
};

template<typename Func, typename... Args>
void ThreadPool::thread_pool_executor(Func func, Args... args) {
    while (running) {
        while (free_indecies.size() > 0 && running) {
            int i = free_indecies.front();
            pool[i] = std::make_unique<std::thread>(&ThreadPool::worker<Func, Args...>, this, &avalability[i], func, args...);
            free_indecies.pop();
            avalability[i] = false;
            current_iter++;
            if (current_iter == total_iter) running = false;
        }
        for (int i = 0; i < max_threads; i++) {
            if (avalability[i] && pool[i]->joinable()) {
                pool[i]->join();
                free_indecies.push(i);
            }
        }
    }
    for (int i = 0; i < max_threads; i++) {
        if (pool[i]->joinable()) {
            pool[i]->join();
        }
    }
    reset();
}

template<typename Func, typename... Args>
void ThreadPool::worker(bool* complete, Func func, Args... args) {
    std::invoke(func, args...);
    *complete = true;
}
