/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>

std::string university;

class student
{
    std::string name;
    std::string student_id;
    mutable int num_courses;
    
    public:
    static float total_gpa;
    student(std::string name, std::string student_id, int num_courses) : name(name), student_id(student_id), num_courses(num_courses)
    {
    }
    
    //const function
    void add_course() const
    {
        num_courses++;
        std::cout << "Total courses enrolled = " << num_courses << std::endl;
        total_gpa++; // const allows static members to be updated. because it is not linked to 'this' pointer
        //student_id = name+student_id; // Not allowed because the 'this' pointer passed to this function is const which does not allow non-mutable members to be updated
    }
    
    static void change_gpa(float gpa)
    {
        total_gpa = gpa;
        std::cout << "GPA changed to " << total_gpa << std::endl;
        //std::cout << "Student = " << name << std::endl; // Cannot access non-static members from a static function
    }
    
    void print()
    {
        //university = "university";
        std::cout << "Student = " << name << ", id = " << student_id << ", num_courses = " << num_courses << std::endl;
        std::cout << "university = " << university << std::endl;
    }
    
};
float student::total_gpa = 3.0;

int main()
{
    auto x = 10;
    register int y = 20;
    std::cout << x << ", " << y << std::endl;
    
    extern std::string university;
    university = "state university";
    student s1("John", "10023", 3);
    s1.add_course();
    s1.print();
    std::cout << "Total GPA = " << student::total_gpa << std::endl;
    
    const student s2("Joe", "19800", 2);
    s2.add_course(); // Allowed because num_courses is mutable 
    //s2.print(); // Not allowed
    student::change_gpa(5.0);
    std::cout << "Total GPA = " << s2.total_gpa << std::endl;

    return 0;
}
