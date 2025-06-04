 // یوسف ملک محمد
 // کد دانشجویی 4036013107

 #include <iostream>
 #include "fstream"

 using namespace std;
 
 class User // کاربر سیستم
 {
   public:
    User();
    
    
    
    ~User();
   protected :
    string username;
    string password;
    int userID;
    string name;
   };
 
 User::User()
 {
 }
 
 User::~User()
 {
 }

 class Employee // کارمندان
 {
 public:
    Employee();

    virtual void editDetails() = 0;
    virtual void getEmployeeType() = 0;
    virtual void calculateMonthlySalary() = 0 ;
    virtual void displayDetails() = 0;    
    ~Employee();
 
 protected :
    string name;
    int EmployeeId;
    string department;
 };
 
 Employee::Employee()
 {
 }
 
 Employee::~Employee()
 {
 }



 class FullTimeEmployee : public Employee
 {
 public:
    FullTimeEmployee();

   //  double monthlySalaryBase(){

   //      return ;
   //  }
    
    ~FullTimeEmployee();
 
 private:
    
 };
 
 FullTimeEmployee::FullTimeEmployee()
 {
 }
 
 FullTimeEmployee::~FullTimeEmployee()
 {
 }

 class PartTimeEmployee : public Employee
 {
 public:
    PartTimeEmployee();

   //  double hourlyRate(){

   //      return ;
   //  }

   //  int hoursWorked(){

   //      return ;
   //  }

    ~PartTimeEmployee();
 
 private:
    
 };
 
 PartTimeEmployee::PartTimeEmployee()
 {
 }
 
 PartTimeEmployee::~PartTimeEmployee()
 {
 }

 class ContractorEmployee : public Employee // پیمانکاری
 {
 public:
    ContractorEmployee();

   //  double contractValue(){

   //      return ;
   //  }

   //  int contractDurationMonths (){

   //      return ;
   //  }
    
    ~ContractorEmployee();
 
 private:
    
 };
 
 ContractorEmployee::ContractorEmployee()
 {
 }
 
 ContractorEmployee::~ContractorEmployee()
 {
 }





 class DepartmentManager: public User  // مدیر سیستم
 {
 public:
    DepartmentManager();
    

    ~DepartmentManager();
 private:
    
 };
 
 DepartmentManager::DepartmentManager()
 {
 }
 
 DepartmentManager::~DepartmentManager()
 {
 }


 int main()
 {

   // ifstream fin("D:\\class\\unity\\c++2\\project\\text.txt");
   // getline(fin , temp);


   User DepartmentManager[100] ;

   DepartmentManager[0].userID = 123456;
   DepartmentManager[0].password = "789012";
   DepartmentManager[0].username = "345678";
   DepartmentManager[0].name = "Ali";


   cout <<    DepartmentManager[0].userID << "\n"
         <<   DepartmentManager[0].password << "\n"
         <<   DepartmentManager[0].username << "\n"
         <<   DepartmentManager[0].name << "\n";


   

     
     return 0;
 }
