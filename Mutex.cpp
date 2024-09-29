#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

template <typename T>
class thread_safe_stack
{
    std::vector<T> array;
    int top_index;
    std::mutex mtx;
    
    public:
    thread_safe_stack() { top_index = -1; }
    
    void push(T element)
    {
        std::lock_guard<std::mutex> lock(mtx);
        array.push_back(element);
        top_index++;
    }
    
    void pop()
    {
        std::lock_guard<std::mutex> lock(mtx);
        if(top_index >= 0)
        {
            top_index--;
            array.pop_back();
        }
    }
    
    T& top()
    {
        std::lock_guard<std::mutex> lock(mtx);
        return array.back();
    }
};

template <typename T>
class stack_from_vector
{
    std::vector<T> array;
    int top_index;
    
    public:
    stack_from_vector() { top_index = -1; }
    
    void push(T element)
    {
        array.push_back(element);
        top_index++;
    }
    
    void pop()
    {
        if(top_index >= 0)
        {
            top_index--;
            array.pop_back();
        }
    }
    
    T& top()
    {
        return array.back();
    }
};

// Push and pop by threads happen together
void mixed_thread_execution()
{
    thread_safe_stack<int> s;
    thread_local int thread_id = -1;
    
    auto populate_stack = [](thread_safe_stack<int> &s, int id){
        thread_id = id;
        std::cout << "Thread ID = " << thread_id << std::endl;

      for(int i=1; i<=100; ++i)
        s.push(i); // The 3 threads first push 300 elements together
       
      for(int i=1; i<=90; ++i)
        s.pop(); // Then pop 270 elements together
      
      for(int i=1; i<=10; ++i)
      {
        std::cout << s.top() << std::endl; // Prints the last 30 elements in the stack, this order can vary in each run based on thread execution
        s.pop();
      }
      std::cout << "-------------------------------------" << std::endl;
    };
    
    std::vector<std::thread> th;
    for(int i=1; i<=3; ++i)
    {
        th.push_back(std::thread(populate_stack, std::ref(s), i));
    }
    
    for(int i=0; i<3; ++i)
        th[i].join();
}

// Threads may not execute in order, but all push and pop functions happen thread by thread
void inorder_thread_execution()
{
    stack_from_vector<int> s;
    thread_local int thread_id = -1;
    std::mutex mtx;
    
    auto populate_stack = [](stack_from_vector<int> &s, int id, std::mutex &mtx){
        std::lock_guard<std::mutex> lock(mtx);
        thread_id = id;
        std::cout << "Thread ID = " << thread_id << std::endl;

      for(int i=1; i<=100; ++i)
        s.push(i);
       
      for(int i=1; i<=90; ++i)
        s.pop();
      
      for(int i=1; i<=10; ++i)
      {
        std::cout << s.top() << std::endl;
        s.pop();
      }
      std::cout << "-------------------------------------" << std::endl;
    };
    
    std::vector<std::thread> th;
    for(int i=1; i<=3; ++i)
    {
        th.push_back(std::thread(populate_stack, std::ref(s), i, std::ref(mtx)));
    }
    
    for(int i=0; i<3; ++i)
        th[i].join();
}

int main()
{
    mixed_thread_execution();
    inorder_thread_execution();
    
    return 0;
}
