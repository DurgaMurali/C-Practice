#include <iostream>
using namespace std;
 
template <typename T>
class complex
{
    private:
    T real;
    T imaginary;
    
    public:
    // Default constructor
    complex()
    {
        this->real = (T)0;
        this->imaginary = (T)0;
    }
    
    // Parameterized constructor
    complex(T real, T imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }
    
    // copy constructor
    /*complex(const complex &obj)
    {
        this->real = obj.real;
        this->imaginary = obj.imaginary;
    }*/
    
    // copy constructor
    complex(const complex &obj)
    {
        *this = obj;
    }
    
    // assignment operator overloading
    void operator=(const complex &obj)
    {
        this->real = obj.real;
        this->imaginary = obj.imaginary;
    }
    
    // Operator overloading
    complex& operator+(const complex<T> &obj)
    {
        complex<T> *result;
        result->real = this->real + obj.real;
        result->imaginary = this->imaginary + obj.imaginary;
        return *result;
    }
    
    // pre-increment operator overloading
    complex& operator++()
    {
        std::cout << "pre-increment\n";
        ++real;
        ++imaginary;
        
        return (*this);
    }
    
    // post-increment operator overloading
    complex& operator++(T)
    {
        std::cout << "post-increment\n";
        complex<T> *result;
        result->real = this->real;
        result->imaginary = this->imaginary;
        this->real++;
        this->imaginary++;
        return *result;
    }
    
    void print()
    {
        std::cout << "Real = " << this->real << ", imaginary = " << this->imaginary << std::endl;
    }
};
 
int main()
{
    complex<int> *obj1 = new complex<int>(10,5);
    obj1->print();
    complex<int> obj2(*obj1);
    obj2.print();
    
    complex<int> *obj3 = new complex<int>(100,50);
    obj3->print();
    
    *obj1 = *obj3;
    obj1->print();
    obj2.print();
    
    complex<int> obj4 = ++(*obj1);
    obj1->print();
    obj4.print();
    
    complex<int> obj5 = (*obj1)++;
    obj1->print();
    obj5.print();
    
    complex<int> obj6 = (*obj1) + obj5;
    obj6.print();

    delete obj1;
    delete obj3;
    
    return 0;
}
