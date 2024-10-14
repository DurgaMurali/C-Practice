#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

class singleton
{
    static singleton* instance;
    static std::mutex mtx;

    singleton()
    {
    }
    
    public:
    int count;
    
    // Make copy constructor unusable
    singleton (const singleton& obj) = delete;
    
    // Make copy by assignment operator unusable
    void operator=(const singleton& obj) = delete;
    
    static void getInstance(singleton **inst)
    {
        if(instance != nullptr)
        {
            std::cout << "Instance already created" << std::endl;
            *inst = instance;
            return;
        }
        
        std::lock_guard<std::mutex> lck(mtx); // lock_guard blocks until mutex is acquired
        if(instance == nullptr) // Check again to ensure that instance was not created while waiting for mutex
        {
            std::cout << "creating new instance" << std::endl;
            instance = new singleton();
        }
            
        *inst = instance;
    }
};

singleton* singleton::instance = nullptr;
std::mutex singleton::mtx;

int main()
{
    std::vector<std::thread> threads;
    std::vector<singleton*> singleton_inst(5);
    for(int i=0; i<5; ++i)
    {
        threads.push_back(std::thread(singleton::getInstance, &singleton_inst[i]));
    }
    
    for(int i=0; i<5; ++i)
    {
        threads[i].join();
    }
    
    std::cout << singleton_inst[0] << std::endl;
    std::cout << singleton_inst[1] << std::endl;
    if(singleton_inst[0] == singleton_inst[1] && singleton_inst[1] == singleton_inst[2] && singleton_inst[2] ==  singleton_inst[3] && singleton_inst[3] == singleton_inst[4])
        std::cout << "Same pointer" << std::endl;
    
    singleton_inst[0]->count = 0;
    std::cout << singleton_inst[0]->count << std::endl;
    singleton_inst[1]->count = 10;
    std::cout << singleton_inst[1]->count << std::endl;
    std::cout << singleton_inst[0]->count << std::endl;
    singleton_inst[2]->count = 20;
    singleton_inst[3]->count = 30;
    singleton_inst[4]->count = 40;
    
    std::cout << singleton_inst[4]->count << std::endl;
    std::cout << singleton_inst[3]->count << std::endl;
    std::cout << singleton_inst[2]->count << std::endl;
    std::cout << singleton_inst[1]->count << std::endl;
    std::cout << singleton_inst[0]->count << std::endl;

    return 0;
}
