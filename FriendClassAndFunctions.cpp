#include<iostream>
#include <vector>

// Forward declaration
class Nurse;

class Doctor
{
    private:
    std::vector<int> patient_records;
    
    public:
    Doctor(std::vector<int> &patient_info)
    {
        patient_records = patient_info;
    }
    
    int diagnose()
    {
        int size = patient_records.size();
        int count = 0;
        
        for(auto i=0; i<size; ++i)
        {
            std::cout << patient_records[i] << ", ";
            count++;
        }
        std::cout << std::endl;
        return count;
    }
    
    // Friend class
    friend class Nurse;
    // Global friend function
    void friend check_patients_attended_by_nurse(Doctor &d, Nurse &n);
};

class patient
{
    public:
    void get_attending_nurse(Nurse &obj);
};

// Nurse is friend class of Doctor, but the reverse is NOT true!
class Nurse
{
    int id;
    int check_in_time;
    int num_patients;
    public:
    Nurse()
    {
        id = 1001;
        check_in_time = 12;
        num_patients = 10;
    }
    
    Nurse(int id, int check_in_time, int num_patients)
    {
        this->id = id;
        this->check_in_time = check_in_time;
        this->num_patients = num_patients;
    }
    
    void check_patient_records(Doctor &obj)
    {
        int size = obj.patient_records.size();
        for(auto i=0; i<size; ++i)
            std::cout << obj.patient_records[i] << ", ";
        std::cout << std::endl;
    }
    
    // Global friend function
    void friend check_patients_attended_by_nurse(Doctor &d, Nurse &n);
    
    // A member function is the friend function of the Nurse class
    void friend patient::get_attending_nurse(Nurse &obj);
};

void patient::get_attending_nurse(Nurse &obj)
{
    std::cout << "Attending nurse = " << obj.id << std::endl;
}

// Global friend function, friend to multiple classes
void check_patients_attended_by_nurse(Doctor &d, Nurse &n)
{
    int size = d.patient_records.size();
    for(auto i=0; i<size; ++i)
        std::cout << d.patient_records[i] << ", ";
    std::cout << std::endl;
    
    std::cout << "Nurse check_in = " << n.check_in_time << ", number of patients attended = " << n.num_patients << std::endl;
    
    //n.patient_records; // Cannot access patient_records using Nurse object outside Nurse class even though it's a friend class
}

int main()
{
    std::vector<int> patient_info = {1, 5, 8, 10, 13, 14, 15, 18, 20};
    Doctor d(patient_info);
    Nurse n(10004, 11, 14);
    
    int count = d.diagnose();
    std::cout << "Count = " << count << std::endl;
    
    n.check_patient_records(d);
    
    check_patients_attended_by_nurse(d, n);
    
    patient p;
    p.get_attending_nurse(n);
}
