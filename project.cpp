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
    << "[1] Add new Employee" << endl
    << "[2] Edit Employee" << endl
    << "[3] Calculating employee salaries" << endl
    << "[4] Display employee list" << endl
    << "[5] Add new Administrator" << endl
    << "[6] logout " << endl
         << "======================" << endl;
}

//======================//
void handleAdminMenu(DepartmentManager* managerLog , Employee* emp[] , DepartmentManager* managers[],int& managerCount) {
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
                    cout << "\n\nI Found your employee!!\n";
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
            int sure=0,empType;
            int filteredIndexes[100] , filteredCount = 0;

            cout << "if you show list or search on list ??"<< endl;
            cout << "[1]show list\n[2]search" << endl;
            
            cin >> sure;
            
            if (sure == 2)
            {
                string name ,type;
                int id;

                cin.ignore();
                cout << "Enter employee name: ";
                getline(cin, name);

                cout << "Enter employee ID: ";
                cin >> id;

                bool found = false;

                for (int i = 0; emp[i] != NULL; i++) {
                    if (emp[i]->getName() == name && emp[i]->getID() == id) {
                        cout << "Employee: " << emp[i]->getName() << endl;
                        cout << "Monthly Salary: " << emp[i]->calculateMonthlySalary() << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Employee not found!" << endl;
                }

            }else if (sure == 1)
            {
                
                
                
                cout << "----- Select Employee to View Salary -----" << endl;
                
                cout << "Select employee type: \n";
                cout << "[1] Full-Time\n[2] Part-Time\n[3] Contractor\n";
                cin >> empType;
                
                if (empType == 1) {
                    cout << "----- Full-Time Employees -----" << endl;
                for (int i = 0; emp[i] != NULL; i++) {
                    if (emp[i]->getEmployeeType() == "Full-Time") {
                        cout << "[" << filteredCount + 1 << "] " << emp[i]->getName() << endl;
                        filteredIndexes[filteredCount] = i; 
                        filteredCount++;
                    }
                }

                if (filteredCount == 0) {
                    cout << "No employees found." << endl;
                    break;
                }
            }
            else if (empType == 2) {
                cout << "----- Part-Time Employees -----" << endl;
                for (int i = 0; emp[i] != NULL; i++) {
                    if (emp[i]->getEmployeeType() == "Part-Time") {
                        cout << "[" << filteredCount + 1 << "] " << emp[i]->getName() << endl;
                        filteredIndexes[filteredCount] = i;
                        filteredCount++;
                    }

                    if (filteredCount == 0) {
                        cout << "No employees found." << endl;
                        break;
                    }
                }}
                else if (empType == 3) {
                    cout << "----- Contractor Employees -----" << endl;
                    for (int i = 0; emp[i] != NULL; i++) {
                        if (emp[i]->getEmployeeType() == "Contractor") {
                            cout << "[" << filteredCount + 1 << "] " << emp[i]->getName() << endl;
                            filteredIndexes[filteredCount] = i; 
                            filteredCount++;
                        }
                    }
                    if (filteredCount == 0) {
                        cout << "No employees found." << endl;
                        break;
                    }
                }
                
                int choice;
                cout << "Enter employee number: ";
                cin >> choice;

                if (choice > 0 && choice <= filteredCount) {
                    int realIndex = filteredIndexes[choice - 1];
                    cout << "Employee: " << emp[realIndex]->getName() << endl;
                    cout << "Monthly Salary: " << emp[realIndex]->calculateMonthlySalary() << " $" << endl;
                } else {
                    cout << "Invalid selection." << endl;
                }

                
                
                break;
            }
        }
        // نمایش کارمندان
        case 4:{
        int index =0 ;
            for (int i = 0; emp[i] != NULL; i++) {
                cout << "[" << index + 1 << "] " << emp[i]->getName() << endl;
                index++;
            }
            if (index == 0) {
                cout << "No employees found." << endl;
                break;
            }
        break;
        }

        // افزودن مدیر جدید
        case 5: {
            string newUsername, newPassword, newName;
            int newID;

            cin.ignore();

            cout << "Enter new manager's username: ";
            getline(cin, newUsername);

            cout << "Enter new manager's password: ";
            getline(cin, newPassword);

            cout << "Enter new manager's name: ";
            getline(cin, newName);

            cout << "Enter new manager's ID: ";
            cin >> newID;

        bool duplicate = false;
        for (int i = 0; i < managerCount; i++) {
            if (managers[i]->getusername() == newUsername) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "Username already exists!" << endl;
        } else {
            managers[managerCount] = new DepartmentManager();
            managers[managerCount]->setter(newUsername, newPassword, newID, newName);
            managerCount++;
            cout << "New manager added successfully!" << endl;
        }


            break;
        }

        case 6:
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

            switch (choice) {
                case 1:
                    handleLogin(managers, managerCount);
                break;
                case 2:
                    return 0;
                default:
                    cout << "Invalid choice" << endl;
            }
        } else {
            // منوی مدیر
            showAdminMenu(loggedInUser->getname());
            handleAdminMenu(loggedInUser , employers , managers ,managerCount );
        }
    }
    
    
    
     
     return 0;
 }
