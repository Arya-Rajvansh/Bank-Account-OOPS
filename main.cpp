#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

const double PI = 3.14159;

int getInt()
{
    int x;
    cin >> x;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Try again: ";
        cin >> x;
    }
    cin.ignore(1000, '\n');
    return x;
}

double getDouble()
{
    double x;
    cin >> x;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid input. Try again: ";
        cin >> x;
    }
    cin.ignore(1000, '\n');
    return x;
}

class InsufficientFunds
{
public:
    string message;

    InsufficientFunds()
    {
        message = "Insufficient funds! Balance is less than the amount.";
    }
};

class BankAccount
{
private:
    double balance;

public:
    BankAccount()
    {
        balance = 0;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            cout << "Amount must be more than 0." << endl;
        }
        else
        {
            balance = balance + amount;
            cout << "Deposited: " << amount << endl;
        }
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Amount must be more than 0." << endl;
        }
        else if (amount > balance)
        {
            throw InsufficientFunds();
        }
        else
        {
            balance = balance - amount;
            cout << "Withdrawn: " << amount << endl;
        }
    }

    double getBalance()
    {
        return balance;
    }

    void setBalance(double b)
    {
        balance = b;
    }

    void saveBalance()
    {
        ofstream file("balance.txt");
        file << balance;
        file.close();
        cout << "Balance saved to file." << endl;
    }

    void loadBalance()
    {
        ifstream file("balance.txt");
        if (!file)
        {
            cout << "No saved balance found." << endl;
            return;
        }
        file >> balance;
        file.close();
        cout << "Balance loaded from file: " << balance << endl;
    }
};

class SavingsAccount : public BankAccount
{
public:

    void apply_interest(double rate)
    {
        double interest = getBalance() * rate / 100;
        setBalance(getBalance() + interest);
        cout << "Interest added: " << interest << endl;
    }
};

void bankSystem(SavingsAccount &acc)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "----- Bank Account System -----" << endl;
        cout << "1. Deposit money" << endl;
        cout << "2. Withdraw money" << endl;
        cout << "3. Apply interest" << endl;
        cout << "4. Display balance" << endl;
        cout << "5. Save balance" << endl;
        cout << "6. Load balance" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        choice = getInt();

        if (choice == 1)
        {
            cout << "Enter amount to deposit: ";
            double amount = getDouble();
            acc.deposit(amount);
        }
        else if (choice == 2)
        {
            cout << "Enter amount to withdraw: ";
            double amount = getDouble();
            try
            {
                acc.withdraw(amount);
            }
            catch (InsufficientFunds e)
            {
                cout << "Error: " << e.message << endl;
            }
        }
        else if (choice == 3)
        {
            cout << "Enter interest rate (%): ";
            double rate = getDouble();
            acc.apply_interest(rate);
        }
        else if (choice == 4)
        {
            cout << "Current balance: " << acc.getBalance() << endl;
        }
        else if (choice == 5)
        {
            acc.saveBalance();
        }
        else if (choice == 6)
        {
            acc.loadBalance();
        }
        else if (choice != 0)
        {
            cout << "Wrong choice." << endl;
        }
    }
}

class Employee
{
protected:
    string name;
    int id;

public:
    Employee(string n, int i)
    {
        name = n;
        id = i;
    }

    virtual double calculate_pay()
    {
        return 0;
    }

    virtual void display()
    {
        cout << "ID: " << id << ", Name: " << name << endl;
    }

    virtual ~Employee()
    {
    }
};

class FullTimeEmployee : public Employee
{
private:
    double salary;

public:
    FullTimeEmployee(string n, int i, double s) : Employee(n, i)
    {
        salary = s;
    }

    double calculate_pay()
    {
        return salary;
    }

    void display()
    {
        cout << "Full Time Employee" << endl;
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Fixed salary: " << salary << endl;
    }
};

class PartTimeEmployee : public Employee
{
private:
    double rate;
    double hours;

public:
    PartTimeEmployee(string n, int i, double r, double h) : Employee(n, i)
    {
        rate = r;
        hours = h;
    }

    double calculate_pay()
    {
        return rate * hours;
    }

    void display()
    {
        cout << "Part Time Employee" << endl;
        cout << "ID: " << id << ", Name: " << name << endl;
        cout << "Hourly rate: " << rate << ", Hours worked: " << hours << endl;
    }
};

void payrollSystem()
{
    vector<Employee*> employees;

    cout << endl;
    cout << "----- Employee Payroll System -----" << endl;
    cout << "How many employees? ";
    int n = getInt();

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << "Employee " << (i + 1) << endl;
        cout << "1. Full Time  2. Part Time : ";
        int type = getInt();

        cout << "Enter id: ";
        int id = getInt();
        cout << "Enter name: ";
        string name;
        getline(cin, name);

        if (type == 1)
        {
            cout << "Enter fixed salary: ";
            double salary = getDouble();
            employees.push_back(new FullTimeEmployee(name, id, salary));
        }
        else if (type == 2)
        {
            cout << "Enter hourly rate: ";
            double rate = getDouble();
            cout << "Enter hours worked: ";
            double hours = getDouble();
            employees.push_back(new PartTimeEmployee(name, id, rate, hours));
        }
        else
        {
            cout << "Wrong type. Employee not added." << endl;
        }
    }

    cout << endl;
    cout << "===== Employee Details =====" << endl;
    for (int i = 0; i < employees.size(); i++)
    {
        employees[i]->display();
        cout << "Pay: " << employees[i]->calculate_pay() << endl;
        cout << "---------------------------" << endl;
    }

    for (int i = 0; i < employees.size(); i++)
    {
        delete employees[i];
    }
}

class Shape
{
public:

    virtual double area() = 0;
    virtual double perimeter() = 0;
    virtual string getName() = 0;

    virtual ~Shape()
    {
    }
};

class Circle : public Shape
{
private:
    double radius;

public:
    Circle(double r)
    {
        radius = r;
    }

    double area()
    {
        return PI * radius * radius;
    }

    double perimeter()
    {
        return 2 * PI * radius;
    }

    string getName()
    {
        return "Circle";
    }
};

class Rectangle : public Shape
{
private:
    double length;
    double width;

public:
    Rectangle(double l, double w)
    {
        length = l;
        width = w;
    }

    double area()
    {
        return length * width;
    }

    double perimeter()
    {
        return 2 * (length + width);
    }

    string getName()
    {
        return "Rectangle";
    }
};

class Triangle : public Shape
{
private:
    double a, b, c;

public:
    Triangle(double x, double y, double z)
    {
        a = x;
        b = y;
        c = z;
    }

    double area()
    {
        double s = (a + b + c) / 2;
        return sqrt(s * (s - a) * (s - b) * (s - c));
    }

    double perimeter()
    {
        return a + b + c;
    }

    string getName()
    {
        return "Triangle";
    }
};

void shapeHierarchy()
{
    vector<Shape*> shapes;

    cout << endl;
    cout << "----- Shape Hierarchy -----" << endl;
    cout << "How many shapes? ";
    int n = getInt();

    for (int i = 0; i < n; i++)
    {
        cout << endl;
        cout << "Shape " << (i + 1) << endl;
        cout << "1. Circle  2. Rectangle  3. Triangle : ";
        int type = getInt();

        if (type == 1)
        {
            cout << "Enter radius: ";
            double radius = getDouble();
            shapes.push_back(new Circle(radius));
        }
        else if (type == 2)
        {
            cout << "Enter length: ";
            double length = getDouble();
            cout << "Enter width: ";
            double width = getDouble();
            shapes.push_back(new Rectangle(length, width));
        }
        else if (type == 3)
        {
            cout << "Enter side a: ";
            double a = getDouble();
            cout << "Enter side b: ";
            double b = getDouble();
            cout << "Enter side c: ";
            double c = getDouble();

            if (a + b > c && a + c > b && b + c > a)
            {
                shapes.push_back(new Triangle(a, b, c));
            }
            else
            {
                cout << "These sides cannot make a triangle." << endl;
            }
        }
        else
        {
            cout << "Wrong type. Shape not added." << endl;
        }
    }

    cout << endl;
    cout << "===== Shape Results =====" << endl;
    for (int i = 0; i < shapes.size(); i++)
    {
        cout << shapes[i]->getName() << endl;
        cout << "Area: " << shapes[i]->area() << endl;
        cout << "Perimeter: " << shapes[i]->perimeter() << endl;
        cout << "---------------------------" << endl;
    }

    for (int i = 0; i < shapes.size(); i++)
    {
        delete shapes[i];
    }
}

struct Book
{
    string isbn;
    string title;
    string author;
    bool available;
};

class Library
{
private:
    vector<Book> books;
    map<string, Book> isbnMap;

public:

    void addBook()
    {
        Book b;
        cout << "Enter ISBN: ";
        getline(cin, b.isbn);

        if (isbnMap.find(b.isbn) != isbnMap.end())
        {
            cout << "A book with this ISBN already exists." << endl;
            return;
        }

        cout << "Enter title: ";
        getline(cin, b.title);
        cout << "Enter author: ";
        getline(cin, b.author);
        b.available = true;

        books.push_back(b);
        isbnMap[b.isbn] = b;
        cout << "Book added." << endl;
    }

    void removeBook()
    {
        string isbn;
        cout << "Enter ISBN of the book to remove: ";
        getline(cin, isbn);

        if (isbnMap.find(isbn) == isbnMap.end())
        {
            cout << "Book not found." << endl;
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].isbn == isbn)
            {
                books.erase(books.begin() + i);
                break;
            }
        }

        isbnMap.erase(isbn);
        cout << "Book removed." << endl;
    }

    void showBook(Book b)
    {
        cout << "ISBN: " << b.isbn << endl;
        cout << "Title: " << b.title << endl;
        cout << "Author: " << b.author << endl;
        if (b.available)
        {
            cout << "Status: Available" << endl;
        }
        else
        {
            cout << "Status: Not available" << endl;
        }
        cout << "---------------------------" << endl;
    }

    void searchByTitle()
    {
        string title;
        cout << "Enter title to search: ";
        getline(cin, title);

        bool found = false;
        for (int i = 0; i < books.size(); i++)
        {
            if (books[i].title == title)
            {
                showBook(books[i]);
                found = true;
            }
        }

        if (!found)
        {
            cout << "No book found with this title." << endl;
        }
    }

    void searchByIsbn()
    {
        string isbn;
        cout << "Enter ISBN to search: ";
        getline(cin, isbn);

        map<string, Book>::iterator it = isbnMap.find(isbn);
        if (it != isbnMap.end())
        {
            showBook(it->second);
        }
        else
        {
            cout << "Book not found." << endl;
        }
    }

    void displayAll()
    {
        if (books.size() == 0)
        {
            cout << "No books in the library." << endl;
            return;
        }

        for (int i = 0; i < books.size(); i++)
        {
            showBook(books[i]);
        }
    }

    void saveToFile()
    {
        ofstream file("library.txt");
        for (int i = 0; i < books.size(); i++)
        {
            file << books[i].isbn << "|" << books[i].title << "|"
                 << books[i].author << "|" << books[i].available << endl;
        }
        file.close();
        cout << "Books saved to file." << endl;
    }

    void loadFromFile()
    {
        ifstream file("library.txt");
        if (!file)
        {
            cout << "No saved file found." << endl;
            return;
        }

        books.clear();
        isbnMap.clear();

        Book b;
        while (getline(file, b.isbn, '|'))
        {
            getline(file, b.title, '|');
            getline(file, b.author, '|');
            file >> b.available;
            file.ignore(1000, '\n');

            books.push_back(b);
            isbnMap[b.isbn] = b;
        }
        file.close();
        cout << "Books loaded from file." << endl;
    }
};

void libraryManager(Library &lib)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "----- Mini Library Manager -----" << endl;
        cout << "1. Add book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Search book by title" << endl;
        cout << "4. Search book by ISBN" << endl;
        cout << "5. Display all books" << endl;
        cout << "6. Save books to file" << endl;
        cout << "7. Load books from file" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        choice = getInt();

        if (choice == 1)
        {
            lib.addBook();
        }
        else if (choice == 2)
        {
            lib.removeBook();
        }
        else if (choice == 3)
        {
            lib.searchByTitle();
        }
        else if (choice == 4)
        {
            lib.searchByIsbn();
        }
        else if (choice == 5)
        {
            lib.displayAll();
        }
        else if (choice == 6)
        {
            lib.saveToFile();
        }
        else if (choice == 7)
        {
            lib.loadFromFile();
        }
        else if (choice != 0)
        {
            cout << "Wrong choice." << endl;
        }
    }
}

class Student
{
private:
    string name;
    vector<int> marks;
    int total;
    double average;
    char grade;

public:

    void setData(int subjects)
    {
        cout << "Enter student name: ";
        getline(cin, name);

        marks.clear();
        total = 0;

        for (int i = 0; i < subjects; i++)
        {
            cout << "Enter marks for subject " << (i + 1) << " (out of 100): ";
            int m = getInt();
            while (m < 0 || m > 100)
            {
                cout << "Marks must be between 0 and 100. Enter again: ";
                m = getInt();
            }
            marks.push_back(m);
            total = total + m;
        }

        average = (double)total / subjects;

        if (average >= 90)
            grade = 'A';
        else if (average >= 80)
            grade = 'B';
        else if (average >= 70)
            grade = 'C';
        else if (average >= 60)
            grade = 'D';
        else
            grade = 'F';
    }

    void display()
    {
        cout << "Name: " << name << endl;
        cout << "Marks: ";
        for (int i = 0; i < marks.size(); i++)
        {
            cout << marks[i] << " ";
        }
        cout << endl;
        cout << "Total: " << total << endl;
        cout << "Average: " << average << endl;
        cout << "Grade: " << grade << endl;
        cout << "---------------------------" << endl;
    }
};

void gradebook(vector<Student> &students)
{
    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "----- Student Gradebook -----" << endl;
        cout << "1. Add student" << endl;
        cout << "2. Display all students" << endl;
        cout << "0. Back to main menu" << endl;
        cout << "Enter your choice: ";
        choice = getInt();

        if (choice == 1)
        {
            cout << "How many subjects? ";
            int subjects = getInt();
            while (subjects <= 0)
            {
                cout << "Subjects must be more than 0. Enter again: ";
                subjects = getInt();
            }

            Student s;
            s.setData(subjects);
            students.push_back(s);
            cout << "Student added." << endl;
        }
        else if (choice == 2)
        {
            if (students.size() == 0)
            {
                cout << "No students added yet." << endl;
            }
            for (int i = 0; i < students.size(); i++)
            {
                students[i].display();
            }
        }
        else if (choice != 0)
        {
            cout << "Wrong choice." << endl;
        }
    }
}

int main()
{
    cout << fixed << setprecision(2);

    SavingsAccount account;
    Library library;
    vector<Student> students;

    account.loadBalance();

    int choice = -1;

    while (choice != 0)
    {
        cout << endl;
        cout << "====================================" << endl;
        cout << "        C++ OOP ASSIGNMENT" << endl;
        cout << "====================================" << endl;
        cout << "1. Bank Account System" << endl;
        cout << "2. Employee Payroll System" << endl;
        cout << "3. Shape Hierarchy" << endl;
        cout << "4. Mini Library Manager" << endl;
        cout << "5. Student Gradebook" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        choice = getInt();

        if (choice == 1)
        {
            bankSystem(account);
        }
        else if (choice == 2)
        {
            payrollSystem();
        }
        else if (choice == 3)
        {
            shapeHierarchy();
        }
        else if (choice == 4)
        {
            libraryManager(library);
        }
        else if (choice == 5)
        {
            gradebook(students);
        }
        else if (choice == 0)
        {
            cout << "Goodbye!" << endl;
        }
        else
        {
            cout << "Wrong choice. Try again." << endl;
        }
    }

    return 0;
}
