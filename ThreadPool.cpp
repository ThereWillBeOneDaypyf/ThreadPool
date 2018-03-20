#include "ThreadPool.h"
#include<iostream>
ThreadPool :: ThreadPool(size_t sz) : stop(false)
{
    for (int i = 0; i < sz; ++i)
    {
        thread_in_pool.emplace_back(
            [&]() {
                while (true)
                {
                    std ::function<void()> task;
                    {
                        std ::unique_lock<std ::mutex> lck(task_mutex);
                        while (!stop && task_queue.empty())
                            thread_condition.wait(lck);
                        if (stop && task_queue.empty())
                            return;
                        task = std ::move(task_queue.front());
                        task_queue.pop();
                    }
                    task();
                }
            });
    }
}

template <typename Fn, typename... Args>
auto ThreadPool :: enqueue(Fn &&fuc, Args &&... args)
    -> std ::future<typename std ::result_of<Fn(Args...)>::type>
{
    typedef typename std::result_of<Fn(Args...)>::type return_type;
    auto task = std :: make_shared<std :: packaged_task<return_type()> >
        (std :: bind(std :: forward<Fn>(fuc), std :: forward<Args>(args)...));
    std :: future<return_type> res = task -> get_future();
    {
        std :: unique_lock<std :: mutex> lck(task_mutex);
        if(stop)
            throw std :: runtime_error("thread pool has stopped");
        task_queue.emplace([task](){ (*task)(); });
    }
    thread_condition.notify_one();
    return res;
}

ThreadPool :: ~ThreadPool()
{
    {
        std :: unique_lock<std :: mutex> lck(task_mutex);
        stop = true;
    }
    thread_condition.notify_all();
    for(auto& running_thread : thread_in_pool)
        running_thread.join();
}