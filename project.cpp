 // یوسف ملک محمد 4036013107
 // محمد حسین محبت 4036013097
 #include <iostream>
 #include <iomanip>
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
         cout << "\033[36mID:\033[0m " << EmployeeId << endl
             << "\033[36mName:\033[0m " << name << endl
             << "\033[36mType:\033[0m Full-Time" << endl
             << "\033[36mSalary:\033[0m $" << monthlySalary << endl
             << "\033[36mDepartment:\033[0m " << department << endl;
   }
    //------------------------

    void editDetails() override {
        double salary;
        cout << "Enter new monthly salary: ";
        while (!(cin >> salary) || salary <= 0) {
            cout << "Invalid salary. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        monthlySalary = salary;
    }


    string getEmployeeType() override {
        return "FullTime";
    }


    ~FullTimeEmployee();
    
 };
 FullTimeEmployee::~FullTimeEmployee() {}

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
        cout << "\033[36mID:\033[0m " << EmployeeId << endl
             << "\033[36mName:\033[0m " << name << endl
             << "\033[36mType:\033[0m Part-Time" << endl
             << "\033[36mHourly Rate:\033[0m $" << hourlyRate << endl
             << "\033[36mHours Worked:\033[0m " << hourlyWorked << endl
             << "\033[36mDepartment:\033[0m " << department << endl;
   }
     //------------------------

    void editDetails() override {
        double rate;
        int hours;

        cout << "Enter new hourly rate: ";
        while (!(cin >> rate) || rate <= 0) {
            cout << "Invalid rate. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Enter new hours worked: ";
        while (!(cin >> hours) || hours <= 0) {
            cout << "Invalid hours. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        hourlyRate = rate;
        hourlyWorked = hours;
    }


    string getEmployeeType() override {
        return "PartTime";
    }


     //------------------------
    ~PartTimeEmployee();

    
 };
 PartTimeEmployee::~PartTimeEmployee() {}

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
        cout << "\033[36mID:\033[0m " << EmployeeId << endl
             << "\033[36mName:\033[0m " << name << endl
             << "\033[36mType:\033[0m Contractor" << endl
             << "\033[36mContract Value:\033[0m $" << contractValue << endl
             << "\033[36mDuration (Months):\033[0m " << contractDurationMonths << endl
             << "\033[36mDepartment:\033[0m " << department << endl;
    }

    string getEmployeeType() override {
        return "Contractor";
    }


    void editDetails() override {
        double value;
        int months;

        cout << "Enter new contract value: ";
        while (!(cin >> value) || value <= 0) {
            cout << "Invalid value. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        cout << "Enter new contract duration (months): ";
        while (!(cin >> months) || months <= 0) {
            cout << "Invalid duration. Enter a positive number: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        contractValue = value;
        contractDurationMonths = months;
    }

    ~ContractorEmployee();
};
ContractorEmployee::~ContractorEmployee() {}

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

void showMainMenu() {
    cout << "===== Employee Management System ===== " << endl;
    cout << "|1| Login" << endl;
    cout << "|2| Exit" << endl;
    cout << "======================================" << endl;
}

//======================//

void handleLogin(DepartmentManager* managers[], int managerCount) {
    string username, password;
    cout << "Enter username: ";
    cin.ignore(1000, '\n');
    getline(cin, username);
    while (username.empty()) {
        cout << "Username cannot be empty. Please enter again: ";
        getline(cin, username);
    }

    cout << "Enter password: ";
    getline(cin, password);
    while (password.empty()) {
        cout << "Password cannot be empty. Please enter again: ";
        getline(cin, password);
    }

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
    cout << "\033[1;36m\n==========================\n";
    cout << " Admin "<< nameAdmin<<  " Control Panel\n";
    cout << "==========================\033[0m\n";

    cout << "[1] Add new Employee" << endl
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
    while (!(cin >> choice)) {
        cout << "Please enter a valid number: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

    switch (choice) {
        // افزودن کارمند جدید
        case 1: {

            bool isFull = true;
            for (int i = 0; i < 100; i++) {
                if (emp[i] == NULL) {
                    isFull = false;
                    break;
                }
            }
            if (isFull) {
                cout << "\033[31m✘ Employee list is full! Cannot add more employees.\033[0m\n";
                break;
            }


            int empType;
            cout << "Select employee type: \n";
            cout << "[1] Full-Time\n[2] Part-Time\n[3] Contractor\n";
            while (!(cin >> empType) || empType < 1 || empType > 3) {
                cout << "Invalid choice. Please enter 1, 2, or 3: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            string name, department;
            int id;
            bool duplicateID;

            cout << "Enter name: ";
            cin.ignore(); 
            getline(cin, name);
            while (name.empty()) {
                cout << "Name cannot be empty. Enter again: ";
                getline(cin, name);
            }

            
            cout << "Enter department: ";
            getline(cin, department);
            while (department.empty()) {
                cout << "Department cannot be empty. Enter again: ";
                getline(cin, department);
            }


            do {
                duplicateID = false;
                cout << "Enter ID: ";
                while (!(cin >> id)) {
                    cout << "Invalid ID. Please enter a number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                for (int j = 0; j < 100 && emp[j] != NULL; j++) {
                    if (emp[j]->getID() == id) {
                        cout << "\033[1;31m✘ This ID is already in use! Please enter a different ID.\033[0m\n";
                        duplicateID = true;
                        break;
                    }
                }
                
            } while (duplicateID);
            bool added = false;

            for (int i = 0; i < 100; i++) {
                if (emp[i] == NULL) {
                    if (empType == 1) {
                        double salary;
                        cout << "Enter monthly salary: ";
                        while (!(cin >> salary) || salary <= 0) {
                            cout << "Invalid salary. Enter a positive number: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        emp[i] = new FullTimeEmployee(name, id, department, salary);
                    }
                    else if (empType == 2) {
                        double rate;
                        int hours;
                        cout << "Enter hourly rate: ";
                        while (!(cin >> rate) || rate <= 0) {
                            cout << "Invalid rate. Enter a positive number: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        cout << "Enter hours worked: ";
                        while (!(cin >> hours) || hours <= 0) {
                            cout << "Invalid hours. Enter a positive number: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        emp[i] = new PartTimeEmployee(name, id, department, rate, hours);
                    }
                    else if (empType == 3) {
                        double value;
                        int months;
                        cout << "Enter contract value: ";
                        while (!(cin >> value) || value <= 0) {
                            cout << "Invalid input. Enter a positive number: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        cout << "Enter contract duration (months): ";
                        while (!(cin >> months) || months <= 0) {
                            cout << "Invalid input. Enter a positive number: ";
                            cin.clear();
                            cin.ignore(1000, '\n');
                        }
                        emp[i] = new ContractorEmployee(name, id, department, value, months);
                    }

                    added = true;
                    cout << "\033[32m✔ Employee added successfully!\033[0m\n";
                    break;
                }
            }
            if (!added) {
                cout << "\033[31m✘ Employee list is full! Cannot add more employees.\033[0m\n";
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
            while (name.empty()) {
                cout << "Name cannot be empty. Please enter again: ";
                getline(cin, name);
            }

            cout << "Enter department: ";
            getline(cin, department);
            while (department.empty()) {
                cout << "Department cannot be empty. Please enter again: ";
                getline(cin, department);
            }

            cout << "Enter ID: ";
            while (!(cin >> id)) {
                cout << "Invalid ID. Please enter a number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            while (id <= 0) {
                cout << "ID must be a positive number: ";
                while (!(cin >> id)) {
                    cout << "Invalid ID. Please enter a number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }
            }

            bool found = false;

            for (int i = 0; emp[i] != NULL; i++) {
                if (
                    emp[i]->getName() == name &&
                    emp[i]->getDepartment() == department &&
                    emp[i]->getID() == id
                ) {
                    cout << "\n\033[32m✔ Employee found:\033[0m\n";
                    emp[i]->displayDetails(); 
                    emp[i]->editDetails(); 

                    found = true;
                    break;
                }
            }

            if (!found) {
                cout << "\033[31m✘ Employee not found!\033[0m\n";
            }

            break;
        }



        // منوی حساب کارمند
        case 3:{
            int sure=0,empType;
            int filteredIndexes[100] , filteredCount = 0;

            cout << "if you show list or search on list ??"<< endl;
            cout << "[1]show list\n[2]search" << endl;
            
            while (!(cin >> sure) || (sure != 1 && sure != 2)) {
                cout << "Please enter 1 or 2: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            
            if (sure == 2)
            {
                string name ,type;
                int id;

                cin.ignore();
                cout << "Enter employee name: ";
                getline(cin, name);
                while (name.empty()) {
                cout << "Name cannot be empty. Enter again: ";
                getline(cin, name);
                }

                cout << "Enter employee ID: ";
                while (!(cin >> id) || id <= 0) {
                    cout << "Invalid ID. Please enter a positive number: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }



                bool found = false;
                int typeChoice;
                cout << "Select employee type:\n[1] FullTime\n[2] PartTime\n[3] Contractor\n";
                while (!(cin >> typeChoice) || typeChoice < 1 || typeChoice > 3) {
                    cout << "Invalid choice. Enter 1, 2, or 3: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                if (typeChoice == 1) type = "FullTime";
                else if (typeChoice == 2) type = "PartTime";
                else type = "Contractor";

                for (int i = 0; emp[i] != NULL; i++) {
                    if (
                        emp[i]->getName() == name &&
                        emp[i]->getID() == id &&
                        emp[i]->getEmployeeType() == type
                    ) {
                        cout << "Employee: " << emp[i]->getName() << endl;
                        cout << "Monthly Salary: " << emp[i]->calculateMonthlySalary() << " $" << endl;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Employee not found!" << endl;
                    break;
                }



            }else if (sure == 1)
            {
                
                
                
                cout << "----- Select Employee to View Salary -----" << endl;
                
                cout << "Select employee type: \n";
                cout << "[1] Full-Time\n[2] Part-Time\n[3] Contractor\n";
                while (!(cin >> empType) || empType < 1 || empType > 3) {
                    cout << "Invalid choice. Please select 1, 2, or 3: ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }

                
                if (empType == 1) {
                    cout << "----- Full-Time Employees -----" << endl;
                for (int i = 0; emp[i] != NULL; i++) {
                    if (emp[i]->getEmployeeType() == "FullTime") {
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
                    if (emp[i]->getEmployeeType() == "PartTime") {
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
                while (!(cin >> choice) || choice < 1 || choice > filteredCount) {
                    cout << "Invalid number. Choose between 1 and " << filteredCount << ": ";
                    cin.clear();
                    cin.ignore(1000, '\n');
                }


                if (choice > 0 && choice <= filteredCount) {
                    int realIndex = filteredIndexes[choice - 1];
                    cout << "Employee: " << emp[realIndex]->getName() << endl;
                    cout << "Monthly Salary: " << emp[realIndex]->calculateMonthlySalary() << " $" << endl;
                } else {
                    cout << "Invalid selection." << endl;
                }

                
                
            }
            break;
        }
        // نمایش کارمندان
        case 4: {
            int index = 0;
            cout << "\n\033[1;36m==== Employee List ====\033[0m\n"; 

            for (int i = 0; emp[i] != NULL; i++) {
                cout << "\033[1;33m[" << index + 1 << "]\033[0m " 
                    << "\033[1;37mName:\033[0m " << emp[i]->getName() << " | "
                    << "\033[1;37mDepartment:\033[0m " << emp[i]->getDepartment() << " | "
                    << "\033[1;37mType:\033[0m " << emp[i]->getEmployeeType() << "\n";
                index++;
            }

            if (index == 0) {
                cout << "\033[1;31mNo employees found!\033[0m\n"; 
            } else {
                cout << "\033[1;32mTotal Employees:\033[0m " << index << "\n\n"; 
            }

            break;
        }


        // افزودن مدیر جدید
        case 5: {
            string newUsername, newPassword, newName;
            int newID;

            if (managerCount >= 100) {
                cout << "\033[31m✘ Cannot add more managers. Maximum capacity reached!\033[0m\n";
                return;
            }


            cin.ignore();

            cout << "Enter new manager's username: ";
            getline(cin, newUsername);
            while (newUsername.empty()) {
            cout << "Username cannot be empty. Enter again: ";
            getline(cin, newUsername);
            }

            cout << "Enter new manager's password: ";
            getline(cin, newPassword);
            while (newPassword.empty()) {
                cout << "Password cannot be empty. Enter again: ";
                getline(cin, newPassword);
            }

            cout << "Enter new manager's name: ";
            getline(cin, newName);
            while (newName.empty()) {
                cout << "Name cannot be empty. Enter again: ";
                getline(cin, newName);
            }

        bool duplicate = false;

        do {
            cout << "Enter new manager's ID: ";
            while (!(cin >> newID) || newID <= 0) {
                cout << "Invalid ID. Enter a positive number: ";
                cin.clear();
                cin.ignore(1000, '\n');
            }

            duplicate = false; 
            for (int j = 0; j < managerCount; j++) {
                if (managers[j]->getUserID() == newID) {
                    duplicate = true;
                    break;
                }
            }

            if (duplicate) {
                cout << "\033[31m✘ This ID is already in use. Please choose another.\033[0m\n";
            }

        } while (duplicate);

        duplicate = false;
        for (int i = 0; i < managerCount; i++) {
            if (managers[i]->getusername() == newUsername) {
                duplicate = true;
                break;
            }
        }

        if (duplicate) {
            cout << "Username already exists!" << endl;
        } else {
            if (managerCount >= 100) {
                cout << "\033[31m✘ Cannot add more managers. Maximum capacity reached!\033[0m\n";
            } else {
                managers[managerCount] = new DepartmentManager();
                managers[managerCount]->setter(newUsername, newPassword, newID, newName);
                managerCount++;
                cout << "\033[32m✔ Manager added successfully!\033[0m\n";
            }
        }


            break;
        }

        case 6:
        loggedInUser = NULL; 
        cout << "Logged out successfully!" << endl;
        break;

        default:
            cout << endl << "Invalid choice!" << endl;
    }
}

void loadEmployeesFromFile(Employee* employers[], const char* filename) {
    ifstream file("d:\\class\\unity\\c++2\\project\\text.txt");
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return;
    }

    int index = 0;
    string line;

    while (getline(file, line) && index < 100) {

        istringstream fin(line);
        string empType, name, department;
        int id;

        fin >> empType >> name >> id;
        fin >> department;

        if (empType == "FullTime") {
            double salary;
            fin >> salary;
            employers[index++] = new FullTimeEmployee(name, id, department, salary);
        }
        else if (empType == "PartTime") {
            double rate;
            int hours;
            fin >> rate >> hours;
            employers[index++] = new PartTimeEmployee(name, id, department, rate, hours);
        }
        else if (empType == "Contractor") {
            double value;
            int duration;
            fin >> value >> duration;
            employers[index++] = new ContractorEmployee(name, id, department, value, duration);
        }
    }

    file.close();
}




 int main()
 {
    cout << "\033[1;34mWelcome to the Employee Management System!\033[0m\n";
    
    DepartmentManager* managers[100] = {NULL};
    Employee *employers[100] = {NULL};

    int managerCount = 0;

    loadEmployeesFromFile(employers, "text.txt");
    
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
    cout << "Enter your choice: ";
    while (!(cin >> choice) || (choice != 1 && choice != 2)) {
        cout << "Invalid choice. Please enter 1 or 2: ";
        cin.clear();
        cin.ignore(1000, '\n');
    }

            switch (choice) {
                case 1:
                handleLogin(managers, managerCount);
                break;
            
                case 2:
                exit(0);
    
                default:
                    cout << "Invalid choice" << endl;
            }
        } else {
            // منوی مدیر
            showAdminMenu(loggedInUser->getname());
            handleAdminMenu(loggedInUser , employers , managers ,managerCount );
        }
    }
    
    for (int i = 0; i < managerCount; i++) {
        delete managers[i];
    }

     return 0;
 }
