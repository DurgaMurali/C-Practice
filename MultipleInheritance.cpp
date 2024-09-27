#include<iostream>
using namespace std;
 
class car
{
    int seat_capacity;
    int mileage;
    
    public:
    car()
    {
        std::cout << "car default constructor" << std::endl;
    }
    
    car(int num_seats, int mileage)
    {
        std::cout << "car parameterized constructor" << std::endl;
        seat_capacity = num_seats;
        this->mileage = mileage;
    }
    
    void show()
    {
        std::cout << "Seat Capacity = " << seat_capacity << ", mileage = " << mileage << std::endl;
    }
};

class fuel_car : virtual public car
{
    int tank_capacity;
    
    public:
    fuel_car()
    {
        std::cout << "fuel_car default constructor" << std::endl;
    }
    
    fuel_car(int num_seats, int mileage, int tank_capacity) : car(num_seats, mileage)
    {
        std::cout << "fuel_car parameterized constructor" << std::endl;
        this->tank_capacity = tank_capacity;
    }
    
    /*void show()
    {
        car::show();
        std::cout <<"tank_capacity = " << tank_capacity << std::endl;
    }*/
};

class electric_car : virtual public car
{
    int battery_capacity;
    
    public:
    electric_car()
    {
        std::cout << "electric_car default constructor" << std::endl;
    }
    
    electric_car(int num_seats, int mileage, int battery_capacity) : car(num_seats, mileage)
    {
        std::cout << "electric_car parameterized constructor" << std::endl;
        this->battery_capacity = battery_capacity;
    }
    
    /*void show()
    {
        car::show();
        std::cout <<"battery_capacity = " << battery_capacity << std::endl;
    }*/
};

class hybrid_car : public fuel_car, public electric_car
{
    public:
    // If car's parameterized constructor is not called here, car's default constructor will be called after adding virtual keyword although fuel_car and electric_car explicitly call parameterized constructor
    // Although car() is called last, it's the base class and its constructor is called first! Then, it follows order
    hybrid_car(int num_seats, int mileage, int tank_capacity, int battery_capacity) : fuel_car(num_seats, mileage, tank_capacity), electric_car(num_seats, mileage, battery_capacity), car(num_seats, mileage)
    {
    }
};

int main()
{
    hybrid_car hy(4, 25, 18, 150);

    // Diamond Problem
    //hy.show(); // show is ambiguous because a copy is inherited from both fuel_car and electric_car. Add virtual keyword
    //hy.show(); // Ambiguous again, because show is re-defined in both fuel_car and electric_car. Virtual will not help!
    
    hy.show();
    return 0;
}
