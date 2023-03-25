#include "threadpool.h"
#include <iostream>

ThreadPool::ThreadPool(int thds, int it) : max_threads(thds), total_iter(it) {
    pool = (Thread*) malloc(sizeof(Thread) * max_threads);
    avalability = (bool*) malloc(sizeof(bool) * max_threads);
    reset();
}

ThreadPool::~ThreadPool() {
    free(pool);
    free(avalability);
}

void ThreadPool::reset() {
    running = true;
    current_iter = 0;
    free_indecies = std::queue<int>();
    for (int i = 0; i < max_threads; i++) {
        free_indecies.push(i);
        avalability[i] = true;
    }
}