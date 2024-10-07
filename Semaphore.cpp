/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <thread>

class Semaphore
{
    std::mutex mtx;
    std::condition_variable cv;
    int count;
    
    public:
    Semaphore(int size) : count(size) {}
    
    void sem_wait()
    {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this]{return count>0;});
        count--;
    }
    
    void sem_signal()
    {
        std::unique_lock<std::mutex> lock(mtx);
        count++;
        cv.notify_one();
    }
    
};

void write_nums(Semaphore &s, int size)
{
    s.sem_wait();
    for(int i=1; i<=size; ++i)
        std::cout << i << ", ";
    std::cout << std::endl;
    s.sem_signal();
}

int main()
{
    Semaphore s(1); // Binary semaphore
    // counting semaphore
    //Semaphore s(5);
    std::thread threads[5];
    for(int i=0; i<5; ++i)
    {
        threads[i] = std::thread(write_nums, std::ref(s), 10);
    }
    
    for(int i=0; i<5; ++i)
        threads[i].join();
        
    return 0;
}
