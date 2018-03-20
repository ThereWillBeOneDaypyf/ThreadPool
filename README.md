# ThreadPool

> 基于[https://github.com/progschj/ThreadPool](https://github.com/progschj/ThreadPool)所写的线程池<br/>

#### 所使用的C++11特性
* thread
* future/package_task
* mutex/unique_lock
* condition_variable(notify_one/notify_all)
* std :: move/std :: forward
* function/bind
* 尾置返回类型


#### 实用实例
<pre><code>
ThreadPool tp(4); // 新建一个拥有四个线程的线程池
std ::　vector< std :: future<int> > future_vector;// 用于存放得到任务结果的future
for(int i = 0;i < 8; ++ i)
    future_vector.emplace_back(tp.enqueue([](){return i * i;}));
for(auto& res : future_vector) // future不可拷贝必须引用
    std :: cout << res.get() << ' ';
system("pause");
</pre></code>

