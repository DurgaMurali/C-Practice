#include <iostream>
#include <vector>
#include <algorithm>

// Function object or Functors
class powerOf
{
    int power;
    
    public:
    powerOf(int num) : power(num) { }
    
    int operator()(int num)
    {
        int result = num;
        for(int i=1; i<power; ++i)
            result = result*num;
        
        std::cout << result << ", ";    
        return result;
    }
};

class integer
{
    int *data;
    
    public:
    integer() : data(new int(0)) { std::cout << "Default constructor" << std::endl; }
    integer(int num) : data(new int(num)) { std::cout << "Parameterized constructor" << std::endl; }
    // Copy constructor
    integer(const integer& in) : data(new int(*(in.data))) { std::cout << "Copy constructor" << std::endl; }
    // Assignment operator
    void operator=(const integer& in)
    {
        *data = *(in.data);
        std::cout << "Assignment operator" << std::endl;
    }
    
    /*// Disable copy constructor and assignment operator to enable move constructor and move assignment operator
    integer(const integer& in) = delete;
    void operator=(const integer& in) = delete;*/
    
    // Move constructor
    integer(integer&& in)
    {
        std::cout << "Move constructor" << std::endl;
        // Move the pointer
        data = in.data;
        in.data = nullptr;
    }

    // Move assignment operator
    void operator=(integer&& in)
    {
        std::cout << "Move assignment operator" << std::endl;
        // First delete this object's resource
        if(this != &in)
            delete data;
        // Move pointer
        data = in.data;
        in.data = nullptr;
    }
    
    ~integer()
    {
        delete data;
        std::cout << "Destructor" << std::endl;
    }
    
    void print()
    {
        std::cout << "Data = " << *data << std::endl;
    }
};

int main()
{
    std::vector<int> arr = {1, 2, 3};
    powerOf p(3);
    std::transform(arr.begin(), arr.end(), arr.begin(), p);
    std::cout << std::endl;

    std::transform(arr.begin(), arr.end(), arr.begin(), powerOf(2));
    std::cout << std::endl;
    
    // Lambda expression
    for_each(arr.begin(), arr.end(), [](int &num){
        num = num + 10;
    });
    for_each(arr.begin(), arr.end(), [](int num){
        std::cout << num << ", ";
    });
    std::cout << std::endl;
    
    std::vector<int>::iterator it = find_if(arr.begin(), arr.end(), [](int num){
       return (num > 50);
    });
    std::cout << "The first element greater than 50 is " << *it << std::endl;
    
    std::cout << "---------------------------------------" << std::endl;
    
    integer in1(10);
    in1.print();
    integer in2(in1);
    in2.print();
    integer in3(30);
    in3.print();
    in1 = in3;
    in1.print();

    // Calling move constructor
    integer in4 = std::move(in1);
    in4.print();
    //in1.print(); // Runtime error as data is deleted

    // Calling move assignment operator
    in4 = std::move(in2);
    in4.print();
    //in2.print(); // Runtime error as data is deleted
    
    return 0;
}
