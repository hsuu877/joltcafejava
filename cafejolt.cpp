#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Employee {
private:
    string id;
    string name;
    string position;
    string type;
    double BasicSalary;
    double HourlyWage;
    double DailyWage;
    int WorkingHours;
    int LeaveDays;
    int OvertimeHours;

public:

    Employee() : BasicSalary(0), HourlyWage(0), DailyWage(0), WorkingHours(0), LeaveDays(0), OvertimeHours(0) {}

    void inputDetails() {
        static const string positions[] = {
            "Barista", "Cashier", "Kitchen Staff", "Cleaner",
            "Waiter/Waitress", "Supervisor"
        };
        static const double salaries[] = {1920, 1790, 1850, 1400, 1700, 2400};


        cout << "\nEmployee Positions        Basic Salaries\n";
        cout << "---------------------   -----------------\n";
        for (int i = 0; i < 6; ++i) {
            cout << i + 1 << ". " << setw(25) << left << positions[i] << "$" << salaries[i] << "\n";
        }


        int posChoice;
        while (true) {
            cout << "Please select a position (1,2,3,4,5,6): ";
            cin >> posChoice;
            if (posChoice >= 1 && posChoice <=6 ) break;
            cout << "Invalid choice! Try again.\n";
        }

        position = positions[posChoice - 1];
        BasicSalary = salaries[posChoice - 1];


        cout << "Enter Employee ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Employee Name: ";
        getline(cin, name);
        cout << "Enter Employee Type (Full-time/Part-time): ";
        getline(cin, type);
        cout << "Enter Working Hours: ";
        cin >> WorkingHours;


        if (type == "F" || type == "f") {
            cout << "Enter Leave Days: ";
            cin >> LeaveDays;
            cout << "Enter Overtime Hours: ";
            cin >> OvertimeHours;
        } else {
            LeaveDays = 0;
            OvertimeHours = 0;
        }


        HourlyWage = BasicSalary / (30 * 8);
        DailyWage = BasicSalary / 30;
    }

    double calculateSalary() const {
        double netSalary = 0;

        if (type == "P" || type == "p") {
            netSalary = WorkingHours * HourlyWage;
        } else {

            double leave_bonus = (LeaveDays == 0) ? 300 : (LeaveDays == 1) ? 200 : (LeaveDays == 2) ? 100 : 0;
            double overtime_pay = OvertimeHours * HourlyWage * 2;
            double penalty = (LeaveDays > 4 && OvertimeHours > 0) ? BasicSalary * 0.01 : 0;
            double income_tax = BasicSalary * 0.02;
            double social_security_tax = 10;

            netSalary = BasicSalary + leave_bonus + overtime_pay - penalty - income_tax - social_security_tax;
        }

        return netSalary;
    }

    void displayDetails() const {
        cout << left << setw(10) << id
             << setw(18) << name
             << setw(15) << position
             << setw(15) << type
             << setw(15) << fixed << setprecision(2) << BasicSalary
             << setw(15) << HourlyWage
             << setw(13) << DailyWage
             << setw(13) << WorkingHours
             << setw(13) << LeaveDays
             << setw(13) << OvertimeHours
             << setw(13) << fixed << setprecision(2) << calculateSalary() << "\n";
    }

    string getType() const {
        return type;
    }

    string getName() const {
        return name;
    }

    string getPosition() const {
        return position;
    }

    double getNetSalary() const {
        return calculateSalary();
    }
};

class EmployeeUtils {
public:
    static void quickSortByNetSalary(Employee employees[], int low, int high) {
        if (low < high) {
            int pi = partitionByNetSalary(employees, low, high);
            quickSortByNetSalary(employees, low, pi - 1);
            quickSortByNetSalary(employees, pi + 1, high);
        }
    }

    static void quickSortByName(Employee employees[], int low, int high) {
        if (low < high) {
            int pi = partitionByName(employees, low, high);
            quickSortByName(employees, low, pi - 1);
            quickSortByName(employees, pi + 1, high);
        }
    }

    static void quickSortByPosition(Employee employees[], int low, int high) {
        if (low < high) {
            int pi = partitionByPosition(employees, low, high);
            quickSortByPosition(employees, low, pi - 1);
            quickSortByPosition(employees, pi + 1, high);
        }
    }

private:
    static int partitionByNetSalary(Employee employees[], int low, int high) {
        double pivot = employees[high].getNetSalary();
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (employees[j].getNetSalary() < pivot) {
                i++;
                swap(employees[i], employees[j]);
            }
        }
        swap(employees[i + 1], employees[high]);
        return (i + 1);
    }

    static int partitionByName(Employee employees[], int low, int high) {
        string pivot = employees[high].getName();
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (employees[j].getName() < pivot) {
                i++;
                swap(employees[i], employees[j]);
            }
        }
        swap(employees[i + 1], employees[high]);
        return (i + 1);
    }

    static int partitionByPosition(Employee employees[], int low, int high) {
        string pivot = employees[high].getPosition();
        int i = (low - 1);

        for (int j = low; j <= high - 1; j++) {
            if (employees[j].getPosition() < pivot) {
                i++;
                swap(employees[i], employees[j]);
            }
        }
        swap(employees[i + 1], employees[high]);
        return (i + 1);
    }
};

class EmployeePayrollSystem {
private:
    Employee employees[100];
    int Employee_Count;

public:
    EmployeePayrollSystem() : Employee_Count(0) {}

    void addEmployee() {
        if (Employee_Count < 100) {
            employees[Employee_Count].inputDetails();
            Employee_Count++;
            cout << "\n<<<Employee added successfully>>>\n";
        } else {
            cout << "#Maximum employee limit reached#\n";
        }
    }

    void displayAllEmployees() const {
        if (Employee_Count == 0) {
            cout << "\nNo employees to display.\n";
            return;
        }

        cout << "\nEmployee Details:\n";
        cout << left << setw(10) << "ID"
             << setw(18) << "Name"
             << setw(15) << "Position"
             << setw(15) << "Type"
             << setw(15) << "Basic Salary"
             << setw(15) << "Hourly Wages"
             << setw(13) << "Daily Wages"
             << setw(13) << "Work Hours"
             << setw(13) << "Leave Days"
             << setw(13) << "Overtime"
             << setw(13) << "Net Salary"
             << "\n";

        cout << string(120, '-') << "\n";

        for (int i = 0; i < Employee_Count; ++i) {
            employees[i].displayDetails();
        }
    }

    void calculateTotalSalary() const {
        double TotalSalary = 0;
        double FullTimeSalary = 0;
        double PartTimeSalary = 0;

        int FullTimeCount = 0, PartTimeCount = 0;

        for (int i = 0; i < Employee_Count; ++i) {
            TotalSalary += employees[i].getNetSalary();
            if (employees[i].getType() == "F" || employees[i].getType() == "f") {
                FullTimeSalary += employees[i].getNetSalary();
                FullTimeCount++;
            } else {
                PartTimeSalary += employees[i].getNetSalary();
                PartTimeCount++;
            }
        }

        cout << "\n--- Monthly report ---\n";
        cout << "Total Monthly Salary: $" << TotalSalary << "\n";
        cout << "Number of Full-Time Employees: " << FullTimeCount << "\n";
        cout << "Full-Time Salary: $" << FullTimeSalary << "\n";
        cout << "Number of Part-Time Employees: " << PartTimeCount << "\n";
        cout << "Part-Time Salary: $" << PartTimeSalary << "\n";
        cout << "Total number of Employees: " << Employee_Count << "\n";
    }

    void sortEmployeesByNetSalary() {
        EmployeeUtils::quickSortByNetSalary(employees, 0, Employee_Count - 1);
        cout << "\nEmployees sorted by net salary successfully.\n";
        displayAllEmployees();
    }

    void sortEmployeesByName() {
        EmployeeUtils::quickSortByName(employees, 0, Employee_Count - 1);
        cout << "\nEmployees sorted by name successfully.\n";
        displayAllEmployees();
    }

    void sortEmployeesByPosition() {
        EmployeeUtils::quickSortByPosition(employees, 0, Employee_Count - 1);
        cout << "\nEmployees sorted by position successfully.\n";
        displayAllEmployees();
    }
};

int main() {
    EmployeePayrollSystem system;

    while (true) {
        cout << "\n   Employee Payroll System \n";
        cout << "1. Addition of Employee\n";
        cout << "2. Showing All Employees\n";
        cout << "3. Calculation Total Salary\n";
        cout << "4. Sort Employees by Net Salary\n";
        cout << "5. Sort Employees by Name\n";
        cout << "6. Sort Employees by Position\n";
        cout << "7. Exit\n";
        cout << "Enter the number that you wanna check (1,2,3,4,5,6,7): ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                system.addEmployee();
                break;
            case 2:
                system.displayAllEmployees();
                break;
            case 3:
                system.calculateTotalSalary();
                break;
            case 4:
                system.sortEmployeesByNetSalary();
                break;
            case 5:
                system.sortEmployeesByName();
                break;
            case 6:
                system.sortEmployeesByPosition();
                break;
            case 7:
                cout << "Exiting the system.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again next time.\n";
        }
    }
}
