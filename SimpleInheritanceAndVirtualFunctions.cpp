#include <iostream>

enum transport_mode
{
    LAND = 1,
    WATER = 2,
    AIR = 3
};

// Abstract class
class vehicle
{
    private:
    std::string make;
    std::string model;
    
    public:
    int mode_of_transportation;
    void set_make_and_model(std::string make, std::string model)
    {
        this->make = make;
        this->model = model;
    }
    
    virtual void set_mode_of_transportation(int mode_of_transportation) = 0;
};

void vehicle::set_mode_of_transportation(int mode_of_transportation)
{
    std::cout << "Pure virtual functions can also be defined in the abstract class, but outside the class definition" << std::endl;
}

class four_wheeler : public vehicle
{
    protected:
    int num_seats;
    float cargo_space;

    public:
    void set_num_seats(int seats)
    {
        std::cout << "class four_wheeler" << std::endl;
        num_seats = seats;
    }
    
    virtual void set_cargo_space(float cargo_space)
    {
        std::cout << "class four_wheeler" << std::endl;
        this->cargo_space = cargo_space;
    }
    
    void set_mode_of_transportation(int mode_of_transportation)
    {
        this->mode_of_transportation = mode_of_transportation;
    }
};

class car : public four_wheeler
{
    bool infotainment;
    bool off_roading;
    float trunk_space;
    
    public:
    car()
    {
        set_mode_of_transportation(LAND);
        infotainment = true;
        off_roading = false;
        trunk_space = 0.0;
    }
    
    void set_infotainment(bool infotainment)
    {
        this->infotainment = infotainment;
    }
    
    void set_off_roading(bool off_roading)
    {
        this->off_roading = off_roading;
    }
    
    // Function overriding
    void set_cargo_space(float cargo_space)
    {
        std::cout << "class car" << std::endl;
        trunk_space = cargo_space;
    }
    
    void set_num_seats(int seats)
    {
        std::cout << "class car" << std::endl;
        num_seats = seats;
    }
};

class jeep : public four_wheeler
{
    std::string engine_type;
    
    public:
    jeep()
    {
        set_mode_of_transportation(LAND);
        engine_type = "";
    }
    
    void set_engine_type(std::string engine_type)
    {
        this->engine_type = engine_type;
    }
};

int main()
{
    car c1;
    c1.set_infotainment(true);
    c1.set_off_roading(false);
    c1.set_cargo_space(12.5);
    c1.set_num_seats(5);
    
    four_wheeler *suv = new car();
    //suv->set_infotainment(true); // Compiler error, it can't access members of car class
    //suv->set_off_roading(false); // Compiler error, it can't access members of car class
    suv->set_cargo_space(16.5);
    suv->set_num_seats(6); // because method is not made virtual, base class pointer cannot access derived class method
    
    car c2;
    four_wheeler *s2 = &c2;
    s2->set_cargo_space(15.2);
    s2->set_num_seats(4); // because method is not made virtual, base class pointer cannot access derived class method
    //s2->set_infotainment(true); // Compiler error, it can't access members of car class
    //s2->set_off_roading(false); // Compiler error, it can't access members of car class

    delete suv;
    
    return 0;
}
