#pragma once
#include <thread>
#include <mutex>
#include <queue>
#include <memory>
#include <mutex>
#include <stdarg.h>

typedef std::unique_ptr<std::thread> Thread;

class ThreadPool {
private:
    Thread* pool;
    bool* avalability;
    std::queue<int> free_indecies;
    std::mutex cout_lock;
    bool running;
    int max_threads;
    int total_iter;
    int current_iter;
    void worker(bool* complete, int count, void (*usr_func)(...), ...);
public:
    ThreadPool(int thds, int it);
    void thread_pool_executor(int count, void (*usr_func)(...), ...);
};
