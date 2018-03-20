#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include<mutex>
#include<memory>
#include<queue>
#include<vector>
#include<mutex>
#include<thread>
#include<functional>
#include<future>
#include<condition_variable>

class ThreadPool 
{
    typedef unsigned int size_t;
    public:
        ThreadPool(size_t);
        ThreadPool(ThreadPool& ) = delete;
        ThreadPool operator=(ThreadPool& ) = delete;
        template<typename Fn,typename... Args>
        auto enqueue(Fn&& fuc,Args&&... args)
            -> std :: future<typename std :: result_of<Fn(Args...)> :: type>;
        ~ThreadPool();
    private:
        std :: mutex task_mutex;
        std :: condition_variable thread_condition;
        std :: vector<std :: thread> thread_in_pool;
        std :: queue<std :: function<void()> > task_queue;
        bool stop;
};

#endif
