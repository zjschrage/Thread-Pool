#include "threadpool.h"
#include "user_code.h"

int main() {
    ThreadPool pool(16, 64);
    pool.thread_pool_executor(&worker);
    pool.thread_pool_executor(&worker2, 1, 2, 'c');
    pool.thread_pool_executor(&worker3_slow, 99);
    std::cout << my_important_work << std::endl;
}
