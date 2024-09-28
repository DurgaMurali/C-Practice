#include <iostream>

class number
{
    int *numPtr;
    
    public:
    void set(int num)
    {
        this->numPtr = new int();
        *(this->numPtr) = num;
    }
    
    void change(int num)
    {
        *(this->numPtr) = num;
    }
    
    void get()
    {
        std::cout << *(this->numPtr) << std::endl;
    }
};

class decimal
{
    int *wholePtr;
    int *fractPtr;
    
    public:
    // Default constructor
    decimal()
    {
        std::cout << "Default constructor" << std::endl;
        wholePtr = new int();
        fractPtr = new int();
    }
    
    // Parameterized constructor
    decimal(int wholeNum, int fractNum)
    {
        std::cout << "Parameterized constructor" << std::endl;
        wholePtr = new int();
        fractPtr = new int();
        *wholePtr = wholeNum;
        *fractPtr = fractNum;
    }
    
    // Copy Constructor, deep copy
    decimal(const decimal& d)
    {
        wholePtr = new int();
        fractPtr = new int();
        *wholePtr = *(d.wholePtr);
        *fractPtr = *(d.fractPtr);
        std::cout << "Copy constructor" << std::endl;
    }
    
    // Destructor, delete resources
    ~decimal()
    {
        std::cout << "Destructor" << std::endl;
        delete wholePtr;
        delete fractPtr;
    }
    
    // Assignmet operator, deep copy
    void operator=(const decimal& d)
    {
        *wholePtr = *(d.wholePtr);
        *fractPtr = *(d.fractPtr);
        std::cout << "Assignment Operator" << std::endl;
    }
    
    void set(int wholeNum, int fractNum)
    {
        *wholePtr = wholeNum;
        *fractPtr = fractNum;
    }
    
    void get()
    {
        std::cout << "Whole Part = " << *wholePtr << ", fraction part = " << *fractPtr << std::endl;
    }
    
};

int main()
{
    number num1;
    num1.set(10);
    num1.get();
    
    // Default copy constructor, shallow copy
    number num2(num1);
    num2.get();
    num1.change(20);
    num1.get();
    num2.get(); // num2 also gets updated to 20 because of shallow copy by default copy constructor
    
    // Default assignment operator overloading, shallow copy
    num2 = num1;
    num1.get();
    num2.get();
    num1.change(30);
    num1.get();
    num2.get(); // num2 also gets updated to 30 because of shallow copy by default assignment operator
    
    decimal d1;
    d1.set(10, 3);
    d1.get();
    
    decimal d2(d1); // Copy constructor will be called when a new object is created
    d2.get();
    
    d1.set(15, 7);
    d1.get();
    d2.get();
    
    d2 = d1; // Assignment operator is called when both pbjects are already created, and one is assigned to another
    d2.get();
    d1.set(18, 9);
    d1.get();
    d2.get();
    
    return 0;
}
