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
    virtual string  getEmployeeType() = 0;

    string getName() { return name; }
    string getDepartment() { return department; }
    int getID() { return EmployeeId; }
    
    ~Employee(){};
 
 protected :
    string name;
    int EmployeeId;
    string department;
 };

//======================//

 class FullTimeEmployee : public Employee {
private:
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

    string getEmployeeType() override {
        return "Full-Time";
    }


    ~FullTimeEmployee();
    
 };

//======================//

 class PartTimeEmployee : public Employee {     //پاره وقت
private:

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

    string getEmployeeType() override {
        return "Part-Time";
    }


     //------------------------
    ~PartTimeEmployee();

    
 };

//======================//
class ContractorEmployee : public Employee {
private:

    double contractValue;
    int contractDurationMonths;

public:
    ContractorEmployee(string name , int id , string dpt, double value , int duration)
        : Employee(name, id, dpt), contractValue(value), contractDurationMonths(duration) {}

    double calculateMonthlySalary() override {
        return contractValue / contractDurationMonths;
    }

    void displayDetails() override {
        cout << "ID:" << EmployeeId << endl
             << "| Name: " << name << endl
             << "| Type : Contractor" << endl
             << "| Contract Value: " << contractValue << endl
             << "| Duration (Months): " << contractDurationMonths << endl
             << "| Department: " << department << endl;
    }

    string getEmployeeType() override {
        return "Contractor";
    }


    void editDetails() override {
        cout << "Enter new contract value: ";
        cin >> contractValue;
        cout << "Enter new duration (months): ";
        cin >> contractDurationMonths;
    }
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
void handleAdminMenu(DepartmentManager* managerLog , Employee* emp[]) {
    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        // افزودن کارمند جدید
        case 1: {

            int empType;
            cout << "Select employee type: \n";
            cout << "[1] Full-Time\n[2] Part-Time\n[3] Contractor\n";
            cin >> empType;

            string name, department;
            int id;

            cout << "Enter name: ";
            cin.ignore(); 
            getline(cin, name);

            cout << "Enter department: ";
            getline(cin, department);

            cout << "Enter ID: ";
            cin >> id;

            for (int i = 0; i < 100; i++) {
                if (emp[i] == NULL) {
                    if (empType == 1) {
                        double salary;
                        cout << "Enter monthly salary: ";
                        cin >> salary;
                        emp[i] = new FullTimeEmployee(name, id, department, salary);
                    }
                    else if (empType == 2) {
                        double rate;
                        int hours;
                        cout << "Enter hourly rate: ";
                        cin >> rate;
                        cout << "Enter hours worked: ";
                        cin >> hours;

                        emp[i] = new PartTimeEmployee(name, id, department, rate, hours);
                    }
                    else if (empType == 3) {
                        double value;
                        int months;
                        cout << "Enter contract value: ";
                        cin >> value;
                        cout << "Enter contract duration (months): ";
                        cin >> months;

                        emp[i] = new ContractorEmployee(name, id, department, value, months);
                    }
                    cout << "Employee added successfully!" << endl;
                    break;
                }
            }

            break;
        }

        // ادیت اطلاعات کارمند
        case 2: {
            string name, department;
            int id;

            cin.ignore(); 
            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter department: ";
            getline(cin, department);

            cout << "Enter ID: ";
            cin >> id;

            bool found = false;

            for (int i = 0; emp[i] != NULL; i++) {
                if (
                    emp[i]->getName() == name &&
                    emp[i]->getDepartment() == department &&
                    emp[i]->getID() == id
                ) {
                    emp[i]->editDetails(); 
                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "Employee not found!" << endl;
            }

            break;
        }

        // منوی حساب کارمند
        case 3:{

            cout << "----- Select Employee to View Salary -----" << endl;

            int empType , index = 0;
            cout << "Select employee type: \n";
            cout << "[1] Full-Time\n[2] Part-Time\n[3] Contractor\n";
            cin >> empType;

            if (empType == 1) {

                    for (int i = 0; emp[i] != NULL; i++) {
                        cout << "[" << index + 1 << "] " << emp[i]->getName() << endl;
                        index++;
                    }

                    if (index == 0) {
                        cout << "No employees found." << endl;
                        break;
                    }
                }
                else if (empType == 2) {
                        cout << "----- Part-Time Employees -----" << endl;
                        for (int i = 0; emp[i] != NULL; i++) {
                            cout << "[" << index + 1 << "] " << emp[i]->getName() << endl;
                            index++;
                        }

                        if (index == 0) {
                            cout << "No employees found." << endl;
                            break;
                        }
                    }
                    else if (empType == 3) {
                        for (int i = 0; emp[i] != NULL; i++) {
                            cout << "[" << index + 1 << "] " << emp[i]->getName() << endl;
                            index++;
                        }

                        if (index == 0) {
                            cout << "No employees found." << endl;
                            break;
                        }
                    }

            int choice;
            cout << "Enter employee number: ";
            cin >> choice;

            if (choice > 0 && choice <= index) {
                int i = choice - 1;
                cout << "Employee: " << emp[i]->getName() << endl;
                cout << "Monthly Salary: " << emp[i]->calculateMonthlySalary() << endl;
            } else {
                cout << "Invalid selection." << endl;
            }
            

            break;
        }
        // case 4
            // نمایش کارمندان

        case 5:
            delete loggedInUser;
            loggedInUser = NULL;
            break;

        default:
            cout << endl << "Invalid choice!" << endl;
    }
}



 int main()
 {
    
    // ifstream fin("D:\\class\\unity\\c++2\\project\\text.txt");
    // getline(fin , temp);
    
    
    DepartmentManager* managers[100] = {NULL};
    Employee *employers[100] = {NULL};

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
            handleAdminMenu(loggedInUser , employers);
        }
    }
    
    
    
     
     return 0;
 }
