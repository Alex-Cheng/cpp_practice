#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <random>
#include <queue>

using namespace std;

int main()
{
    mutex mtx, mtx_prod;
    condition_variable cv;
    condition_variable cv_producer;
    queue<int> tasks;
    constexpr size_t max_tasks = 10;

    auto producer = [&]() {
        while(true)
        {
            {
                //cout << "add a new task..." << endl;
                unique_lock<mutex> lck(mtx);
                if (tasks.size() < max_tasks)
                {
                    int v = rand();
                    tasks.push(v);
                }
            }
            cv.notify_one();
            // {
            //     unique_lock<mutex> lck_prod(mtx_prod);
            //     cv_producer.wait(lck_prod, [&tasks]() { return ; });
            // }            
            // //this_thread::sleep_for(chrono::microseconds(100));
        }
        return 0;
    };

    auto consumer = [&](size_t id) {        
        while(true)
        {
            int value;
            {
                unique_lock<mutex> lck(mtx);
                cv.wait(lck, [&tasks]() {return !tasks.empty(); });
                value = tasks.front();
                tasks.pop();
            }            
            size_t sum;
            for (size_t i = 1; i < value; ++i)
            {
                sum += i;
            }
            cout << "worker[" << id << "]" << " sum of 1..." << value << " = " << sum << endl;
            cv_producer.notify_all();
        }
        return 0;
    };

    std::cout << "Begin..." << std::endl;
    thread p{producer}, c1{consumer, 1}, c2{consumer, 2}, c3{consumer, 3}, c4{consumer, 4};
    thread c5{consumer, 5}, c6{consumer, 6}, c7{consumer, 7}, c8{consumer, 8};
    thread c9{consumer, 9}, c10{consumer, 10}, c11{consumer, 11}, c12{consumer, 12};
    p.join();
    c1.join();
    c2.join();
    c3.join();
    c4.join();
    c5.join();
    c6.join();
    c7.join();
    c8.join();
    std::cout << "End" << std::endl;
}
