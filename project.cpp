 #include <iostream>
 #include "fstream"

 using namespace std;

//======================//

 class User // کاربر سیستم
 {
 protected :
    string username;
    string password;
    int userID;
    string name;

 public:
     User(string uname, string pwd, int id, string name) : username(uname), password(pwd), userID(id), name(name) {};

    //------------------------

    bool identify(string usname, string pwd) {     // احراز هویت
        return (username == usname && password == pwd);
     }
    //------------------------

    string getUsername() {return username;}
    string getPassword() {return password;}

    //------------------------

   };

//======================//

 class Employee // کارمندان
 {
 public:
    Employee(string name , int id , string dpt)
       : name(name), EmployeeId(id), department(dpt) {};

    virtual double calculateMonthlySalary() = 0 ;
    virtual void displayDetails() = 0;
    virtual void editDetails() = 0;
    virtual void getEmployeeType() = 0;

    ~Employee(){};
 
 protected :
    string name;
    int EmployeeId;
    string department;
 };

//======================//

 class FullTimeEmployee : public Employee {

    double monthlySalary;

 public:

    FullTimeEmployee(string name , int id , string dpt , double Salary)
        : Employee(name, id, dpt), monthlySalary(Salary) {};

     //------------------------

   double calculateMonthlySalary() override {
      return monthlySalary;
   }
    //------------------------

    void displayDetails() override {
      cout << "ID:" << EmployeeId << endl
      << "Name: " << name << endl
      << "Type : Full-Time" << endl
      << "Salary: " <<  calculateMonthlySalary() << endl
      << "Department: " << department << endl;
   }
    //------------------------

    void editDetails() override {
      cout << "Enter new monthly salary: ";
      cin >> monthlySalary;
   }

   void getEmployeeType() {
    cout << "Full-Time" << endl;
}

    ~FullTimeEmployee();
    
 };

//======================//

 class PartTimeEmployee : public Employee {     //پاره وقت

     double hourlyRate;
     int hourlyWorked;

 public:
    PartTimeEmployee(string name , int id , string dpt,  double rate ,  double hours)
        : Employee(name, id, dpt), hourlyRate(rate), hourlyWorked(hours) {};
     //------------------------

   double calculateMonthlySalary() override {return hourlyRate * hourlyWorked;}
    //------------------------

    void displayDetails() override {
      cout << "ID:" << EmployeeId << endl
      << "| Name: " << name << endl
      << "| Type : Part-Time" << endl
      << "| Hour lyRate: " << hourlyRate << endl
      << "| Hourly Worked: " << hourlyWorked << endl
      << "| Department: " << department << endl;
   }
     //------------------------

    void editDetails() override {
      cout << "Enter new hourly rate: ";
       cin >> hourlyRate;
       cout << "Enter new hourly worked: ";
       cin >> hourlyWorked;
   }

   void getEmployeeType() {
       cout << "part-Time" << endl;
   }

     //------------------------
    ~PartTimeEmployee();

    
 };

//======================//

 class ContractorEmployee : public Employee{ // پیمانکاری

     double contractValue;
     int contractDurationMonths;

 public:
    ContractorEmployee(string name , int id , string dpt, double value , int duration)
        : Employee(name, id, dpt), contractValue(value), contractDurationMonths(duration) {};
     //------------------------

   double calculateMonthlySalary(){

       return contractValue / contractDurationMonths;
   }
     //------------------------

     void displayDetails() override {
       cout << "ID:" << EmployeeId << endl
       << "| Name: " << name << endl
       << "| Type : Contractor" << endl
       << "| Duration (Months): " << contractValue << endl
       << "| Department: " << department << endl;
   }

   void getEmployeeType() {
    cout << "contract-Time" << endl;
}

     //------------------------
    
    ~ContractorEmployee();

 };

//======================//

 class DepartmentManager: public User  // مدیر سیستم
 {

 public:
   DepartmentManager() : User("", "", 0, "") {}
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
 
 //
 DepartmentManager::~DepartmentManager()
 {
 }


// menu :

DepartmentManager* loggedInUser = NULL;

void showMainMenu() { // منوی اصلی
    cout << "===== Employee Management System ===== " << endl;
    cout << "|1| Login" << endl;
    cout << "|2| Exit" << endl;
    cout << "======================================" << endl;
}

//======================//

void handleLogin(DepartmentManager* managers[], int managerCount) {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < managerCount; i++) {
        if (managers[i] != NULL && managers[i]->identify(username, password)) {
            loggedInUser = managers[i];
            cout << "Logged in!" << endl;
            return;
        }
    }

    cout << "The username or password is incorrect!" << endl;
}


//======================//

void showAdminMenu(string nameAdmin) {
    cout << "===== Admin "<< nameAdmin << " Menu =====" << endl
    << "[1] Add new administrator" << endl
    << "[2] Edit Employee" << endl
    << "[3] Calculating employee salaries" << endl
    << "[4] Display employee list" << endl
    << "[5] logout " << endl
         << "======================" << endl;
}

//======================//

void handleAdminMenu(DepartmentManager* managerLog) {

    int choice;
    cout << "Enter your choice: " ;
    cin >> choice;

    switch (choice) {
        // case 1:

        // case 2 :
            //  منوی ویرایش کارمند
        // case 3
            // منوی حساب کارمند
        // case 4
            // نمایش کارمندان
        case 5:
            delete loggedInUser;
            loggedInUser = NULL;
            break;
        default:
            cout << endl << "Invalid choice !" << endl;
    }
}

 int main()
 {
    
    // ifstream fin("D:\\class\\unity\\c++2\\project\\text.txt");
    // getline(fin , temp);
    
    
    DepartmentManager* managers[100] = {NULL};
    int managerCount = 0;
    
    managers[managerCount] = new DepartmentManager();
    managers[managerCount]->setter("AbbasAli" , "123456" , 987654 , "Ali");
    managerCount++;
    
    
    
    cout <<    managers[0]->getUserID() << "\n"
    <<"@"<<   managers[0]->getusername() << "\n"
    <<   managers[0]->getpassword() << "\n"
    <<   managers[0]->getname() << "\n";
    
    while (true) { // منو
        if (!loggedInUser) {
            showMainMenu();
            int choice;
            cin >> choice;
            cout << endl << endl << endl << endl;

            switch (choice) {
                case 1:
                    handleLogin(managers, managerCount);
                break;
                case 2:
                    return 0;
                default:
                    cout << "Invalid choice" << endl << endl << endl;
            }
        } else {
            // منوی مدیر
            showAdminMenu(loggedInUser->getname());
            handleAdminMenu(loggedInUser);
        }
    }
    
    
    
     
     return 0;
 }
