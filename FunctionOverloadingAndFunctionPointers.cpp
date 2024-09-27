#include<iostream>

// Function overloading
void area(int length)
{
    std::cout << "Area of square = " << length*length << std::endl;
}

void area(int length, int breadth)
{
    std::cout << "Area of rectangle = " << length*breadth << std::endl;
}

// Overloading using const variables NOT allowed
/*void area(const int length)
{
    std::cout << "Const area of square = " << length*breadth << std::endl;
}*/

void area(int *length)
{
    std::cout << "Pointer Area of square = " << (*length)*(*length) << std::endl;
}

// Overloading using const pointers is allowed 
void area(const int *length)
{
    std::cout << "Const pointer Area of square = " << (*length)*(*length) << std::endl;
}

// CANNOT overload with different return types (even with const return types)
/*const int area(int length)
{
    std::cout << "Const return type area of square = " << length*breadth << std::endl;
}*/

// CANNOT overload based on function qualifiers
/*const void area(int length)
{
    std::cout << "Const function area of square = " << length*breadth << std::endl;
}*/

int main()
{
    int length = 10;
    const int breadth = 20;
    area(length);
    area(length, breadth);
    area(&length);
    area(&breadth);
    
    // Mangled names and function pointers
    void (*areaSquareInt)(int) = &area;
    std::cout << typeid(areaSquareInt).name() << std::endl;
    
    void(*areaRectangleInt)(int, int) = &area;
    std::cout << typeid(areaRectangleInt).name() << std::endl;
    
    void (*areaSquareIntPtr)(int*) = &area;
    std::cout << typeid(areaSquareIntPtr).name() << std::endl;
    
    void (*areaSquareConstIntPtr)(const int*) = &area;
    std::cout << typeid(areaSquareConstIntPtr).name() << std::endl;
}
