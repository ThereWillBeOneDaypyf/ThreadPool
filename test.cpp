#include<iostream>
// #include<future>
#include<vector>
#include "ThreadPool.h"
#include "ThreadPool.cpp"
static int j = 0;

int add()
{
    ++j;
    return j * j;
}

int main()
{
    ThreadPool tp(4);
    std :: vector<std :: future<int> > res_future;
    for(int i = 0;i < 10; ++ i)
    {
        res_future.emplace_back(tp.enqueue(add));
    }
    for(auto& final_res : res_future)
        std :: cout << final_res.get() << std :: endl;
    system("pause");
}
