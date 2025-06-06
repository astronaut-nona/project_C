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
      void setter (string user1 , string pass , int id , string user2){
      username = user1;
      password = pass;
      userID = id;
      name = user2;
    }
    int getUserID(){return userID;}
    string getusername(){return username;}
    string getpassword(){return password;}
    string getname(){return name;}

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


   DepartmentManager* managers[100] = {NULL};

   managers[0] = new DepartmentManager();  
   managers[0]->setter("AbbasAli" , "123456" , 987654 , "Ali" );



   cout <<    managers[0]->getUserID() << "\n"
         <<"@"<<   managers[0]->getusername() << "\n"
         <<   managers[0]->getpassword() << "\n"
         <<   managers[0]->getname() << "\n";


   

     
     return 0;
 }
