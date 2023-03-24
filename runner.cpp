#include "threadpool.h"
#include "user_code.h"

int main() {
    ThreadPool pool(4, 16);
    pool.thread_pool_executor(&worker);
    pool.thread_pool_executor(&worker2, 1, 2, 'c');
    std::cout << my_important_work << std::endl;
}
