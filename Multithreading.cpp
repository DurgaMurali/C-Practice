#include <iostream>
#include <vector>
#include <thread>

// Function object or Functors
class powerOf
{
    int power;
    
    public:
    powerOf(int num) : power(num) { }
    
    void operator()(std::vector<int>& arr)
    {
        for(auto j=0; j<arr.size(); ++j)
        {
            int result = arr[j];
            for(int i=1; i<power; ++i)
                result = result*arr[j];
            arr[j] = result;
        }
    }
};

void add(std::vector<int>& arr, int num)
{
    int size = arr.size();
    for(auto i=0; i<size; ++i)
        arr[i] += num;
}

class subtract
{
    int num;
    
    public:
    static int count;
    subtract(int n) : num(n) {}
    
    void minus(std::vector<int> &arr)
    {
        int size = arr.size();
        for(auto i=0; i<size; ++i)
            arr[i] -= num;
    }
    
    static void countArray(std::vector<int> &arr)
    {
        count = arr.size();
    }
};
int subtract::count = 0;

void printArray(std::vector<int> &arr)
{
    int size = arr.size();
    for(auto i=0; i<size; ++i)
        std::cout << arr[i] << ", ";
        
    std::cout << std::endl;
}

int main()
{
    std::vector<int> array = {1, 2, 3, 4, 5};
    auto lambda_expr = [](std::vector<int> &arr, int num){ 
        for(int i=0; i<arr.size(); ++i)
            arr[i] = arr[i]*num; };
            
    // Passing function pointer to thread
    std::thread th1(add, std::ref(array), 3);
    
    powerOf p1(2);
    // Passing function object to thread
    std::thread th2(p1, std::ref(array));
    
    // Passing lambda expression to thread
    std::thread th3(lambda_expr, std::ref(array), -1);
    
    subtract s1(-2);
    // Passing non-static member function to thread
    std::thread th4(&subtract::minus, &s1, std::ref(array));
    
    // Passing a static member function to thread
    std::thread th5(&subtract::countArray, std::ref(array));

    th1.join();
    th2.join();
    th3.join();
    th4.join();
    th5.join();
    
    printArray(array);
    std::cout << "Count = " << subtract::count << std::endl;
    
    return 0;
}
