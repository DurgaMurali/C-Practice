#include <iostream>

// Actual functionality of the library
class baseFeature
{
    public:
    // virtual destructor destroys the derived class object when pointed by a base class object
    virtual ~baseFeature() { }
    virtual void operation() = 0;   
};

class Feature1 : public baseFeature
{
    public:
    void operation()
    {
        std::cout << "Implement operation() function from Feature1" << std::endl;
    }
};

class Feature2 : public baseFeature
{
    public:
    void operation()
    {
        std::cout << "Implement operation() function from Feature2" << std::endl;
    }
};

// The factory class that will be exposed to the client
class baseCreate
{
    public:
    virtual ~baseCreate() { }
    virtual baseFeature* factoryMethod() const = 0;
    
    void someOperation() const
    {
        baseFeature* feature = this->factoryMethod();
        feature->operation();
    }
};

// create an instance of Feature1
class createFeature1 : public baseCreate
{
    public:
    // override keyword explicitly notifies the compiler that there must be a virtual function defined in the base class that is being overridden
    baseFeature* factoryMethod() const override
    {
        baseFeature* feature = new Feature1();
        return feature;
    }
};

// create an instance of Feature2
class createFeature2 : public baseCreate
{
    public:
    baseFeature* factoryMethod() const override
    {
        baseFeature* feature = new Feature2();
        return feature;
    }
};

// client does not know of the implementation details. It only knows the API someOperation()
void clientFunction(const baseCreate& factory)
{
    factory.someOperation();
}

int main()
{
    baseCreate* create1 = new createFeature1();
    clientFunction(*create1);
    
    baseCreate* create2 = new createFeature2();
    clientFunction(*create2);

    return 0;
}
