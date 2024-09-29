#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <vector>

std::condition_variable cv;
std::mutex mtx;
// Atomic variable that assigns value atomically
std::atomic<bool> ready(false);
std::vector<int> global_data;

// Predicate for condition_variable
bool isReady() { return ready; }

void print_thread_id(int id)
{
    // Unique lock acquires the mutex
    std::unique_lock<std::mutex> lck(mtx);
    // Waits until ready becomes true (until all threads are created from main thread).
    // It unlocks the mutex while waiting for other threads to acquire it. When it wakes up after getting notified, it acquires the mutex again.
    // Therefore, there is no need to acquire lock explicitly
    cv.wait(lck, isReady);
    
    std::cout << "Thread ID = " << id << std::endl;
    global_data.push_back(id);
}

int main()
{
    std::vector<std::thread> thread_vec;
    for(int i=1; i<=10; ++i)
        thread_vec.push_back(std::thread(print_thread_id, i));
        
    ready = true;
    // Notify all threads to wake up
    cv.notify_all();
    
    for(int i=0; i<10; ++i)
        thread_vec[i].join();
        
    for(int i=0; i<10; ++i)
        std::cout << global_data[i] << ", ";
    std::cout << std::endl;
    
    return 0;
}
