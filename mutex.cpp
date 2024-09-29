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

int main()
{
    thread_safe_stack<int> s;
    
    auto populate_stack = [](thread_safe_stack<int> &s){
      //std::cout << "Push elements" << std::endl; 
      for(int i=1; i<=100; ++i)
        s.push(i); // The 3 threads first push 300 elements together
       
      //std::cout << "Pop elements" << std::endl;  
      for(int i=1; i<=90; ++i)
        s.pop(); // Then pop 270 elements together
      
      //std::cout << "Top elements" << std::endl;    
      for(int i=1; i<=10; ++i)
      {
        std::cout << s.top() << std::endl; // Prints the last 30 elements
        s.pop();
      }
      std::cout << "-------------------------------------" << std::endl;
    };
    
    std::vector<std::thread> th;
    for(int i=1; i<=3; ++i)
    {
        th.push_back(std::thread(populate_stack, std::ref(s)));
    }
    
    for(int i=0; i<3; ++i)
        th[i].join();
    return 0;
}
