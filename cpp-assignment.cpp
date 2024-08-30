#include <iostream>
using namespace std;

class Employee{
    public:
        int calculateSalary(int salary){
            return salary;
        }
};

class FullTimeEmployee : public Employee{
    public:
    int calculateSalary (int salary) {
        return salary;
    }
        
};

class PartTimeEmployee : public Employee{
    public:
        int calculateSalary(int rate,int hours){
            int salary=rate*hours;
            return salary;
        }
};

class ContractEmployee : public Employee{
    public:
        
};

int main() {
    FullTimeEmployee Kamal;
    PartTimeEmployee Piyal;
    ContractEmployee Damith;
    
    cout<<"Kamal's salary: ";
    int salary=Kamal.calculateSalary(60000);
    cout<<salary<<endl;
    
    cout<<"Piyal's salary: ";
    salary=Piyal.calculateSalary(20,2000);
    cout<<salary<<endl;
    
    cout<<"Damith's salary: ";
    salary=Damith.calculateSalary(30000);
    cout<<salary<<endl;
    
    return 0;
}
