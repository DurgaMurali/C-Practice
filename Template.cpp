#include <iostream>

// Template class
template <typename T, typename U = float>
class complex
{
    private:
    T real;
    U imaginary;
    
    public:
    static T count;
    static char i;
    // Default constructor
    complex()
    {
        this->real = (T)0;
        this->imaginary = (U)0;
        count++;
    }
    
    // Parameterized constructor
    complex(T real, U imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
        count++;
    }
    
    // copy constructor
    complex(const complex &obj)
    {
        *this = obj;
        count++;
    }
    
    void print()
    {
        std::cout << "Real = " << this->real << ", imaginary = " << this->imaginary << i << ", count = " << count << std::endl;
    }
};

// Define the static variable for every (T, U) combination
template <typename T, typename U>
T complex<T, U>::count = (T)0;

template <typename T, typename U>
char complex<T, U>::i = 'i';

// Template class specialization for short datatype
template<>
class complex<short, short>
{
    private:
    int real;
    int imaginary;
    
    public:
    static int count;
    
    complex(int real, int imaginary)
    {
        std::cout << "Constructor of complex<short, short>" << std::endl;
        this->real = real;
        this->imaginary = imaginary;
        count++;
    }
    
    void print()
    {
        std::cout << "Real = " << this->real << ", imaginary = " << this->imaginary << ", count = " << count << std::endl;
    }
};

template<>
int complex<short, short>::count = 0;

// Template function
template <typename T>
T isGreater(T a, T b)
{
    return (a>b) ? a : b;
}

// Template function specialization for string datatype
template<>
std::string isGreater(std::string a, std::string b)
{
    int result = a.compare(b);
    if(result >= 0)
        return a;
    else
        return b;
}

int main()
{
    std::cout << isGreater<int>(10, 35) << std::endl;
    std::cout << isGreater<float>(32.6, 11.3) << std::endl;
    std::cout << isGreater<std::string>("call", "ball") << std::endl;

    complex<float> obj1(22.5, 66.7);
    obj1.print();
    complex<int, int> obj2(55, 33);
    obj2.print();
    
    std::cout << complex<float>::count << std::endl;
    std::cout << complex<int, int>::count << std::endl;
    std::cout << complex<int>::count << std::endl;
    std::cout << complex<float, int>::count << std::endl;
    
    std::cout << complex<float>::i << std::endl;
    std::cout << complex<int, int>::i << std::endl;
    std::cout << complex<int>::i << std::endl;
    std::cout << complex<float, int>::i << std::endl;
    
    complex<short, short> obj3(22, 44);
    obj3.print();
    
    return 0;
}
