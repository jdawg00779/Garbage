#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include "LListIter.h"
#include "LinkedList.h"
#include "Employee.h"
using namespace std;

ifstream& operator>>(ifstream &, LinkedList<Employee>&);
bool readFile(LinkedList<Employee>&);
void menu(LinkedList<Employee>&);
void findEmployee(LinkedList<Employee>&);
void addSale(LinkedList<Employee>&);
void hireEmployee(LinkedList<Employee>&);
void totalSales(LinkedList<Employee>&);
void nameSort(LinkedList<Employee>&);
void salesSort(LinkedList<Employee>&);
void reverse(LinkedList<Employee>&);
bool confirmQuit();

int main()
{
  // create an employee list
  LinkedList<Employee> eList;
 
  if(!readFile(eList)) {
    cerr << "Error opening file" << endl;
    return(1);
  }

  // start the menu
  menu(eList);
  return 0;
}

void menu(LinkedList<Employee>& list)
{
  char selection;
  bool quit=false;

  do {
    cout << endl;
    cout << "-----------------------" << endl;
    cout << " L)ist of Employees" << endl;
    cout << " F)ind an Employee" << endl;
    cout << " H)ire a new employee" << endl;
    cout << " A)dd a Sale" << endl;
    cout << " T)otal Sales" << endl;
    cout << " N)ame sort" << endl;
    cout << " S)ales sort" << endl;
    cout << " R)everse list" << endl;
    cout << " Q)uit" << endl;
    cout << endl;
    cout << "Please make a selection: ";
    cin >> selection;
    cout << endl;

    switch(selection) {
      case 'L':
      case 'l':
        cout << list;
        break;
      case 'H':
      case 'h':
        // need to write this!
        //hireEmployee(list);
        cout << list;
        break;
      case 'F':
      case 'f':
        findEmployee(list);
        break;
      case 'A':
      case 'a':
        addSale(list);
        cout << list;
        break;
      case 'T':
      case 't':
        totalSales(list);
        break;
      case 'N':
      case 'n':
        nameSort(list);
        cout << list;
        break;
      case 'S':
      case 's':
        // need to write this!
        //salesSort(list);
        cout << list;
        break;
      case 'R':
      case 'r':
        // need to write this!
        //reverse(list);
        cout << list;
        break;
      case 'Q':
      case 'q':
        quit=confirmQuit();
        break;
      default:
        cout << "Invalid choice, please try again..." << endl;
    }
  } while(quit==false);
}

// Operator overload that gets from a data file 
// and populates the list with Employees
ifstream& operator>>(ifstream& inf, LinkedList<Employee>& list) {
  Employee P;
  while(inf >> P) {
    list.add(P);
  }
  return inf;
}

// Overloaded << instance for LinkedList<Employee>
ostream& operator<<(ostream &os,const LinkedList<Employee> &list) {
  LListIter<Employee> iter(list);
  while(iter.next()) {
    os << *iter;
  }
  return os;
}

// Confirms whether user wants to quit the program
bool confirmQuit() {
  char confirm;

  cout << "Type 'q' again to confirm!" << endl;
  cin >> confirm;
  
  if(confirm == 'q' || confirm == 'Q') return true;
  cout << "Thanks for staying around!" << endl << endl;
  return false;
}

// open a data file, return false is unsucessful
// read data, return true
bool readFile(LinkedList<Employee>& list)
{
  ifstream infile;
  string fileName;

  cout<<"Please enter the name of the data file: ";
  cin >> fileName;

  infile.open(fileName.c_str());
  if(!infile) return false;

  infile >> list;
  infile.close();
  return true;
}

// locate an employee by name, output info
void findEmployee(LinkedList<Employee>& list) {
  LListIter<Employee> iter(list);
  string name;

  cout << "Please enter employee name: ";
  cin >> name;

  do {
    if((*iter).getName() == name) {
      cout << *iter;
      return;
    }
  } while(iter.next());

  cout << name << " not found..." << endl;
}

// find total sales for all employees
void totalSales(LinkedList<Employee>& list) {
  string name;
  float sale;

  cout << fixed << setprecision(2);
  LListIter<Employee> iter(list);
  float total= 0;
  do {
    Employee E= *iter;
    total+= E.getTotal();
  } while(iter.next());
  cout << "Total employee sales: $" << total;
  cout << endl;
}

// sort employees by name
void nameSort(LinkedList<Employee>& list) {
  list.sortAscend();
}

// Concrete << instance for LinkedList<Employee>
void addSale(LinkedList<Employee>& list) {
  string name;
  float sale;

  cout << "Please enter employee name: ";
  cin >> name;
  // create item to use in search
  Employee Eold(name);
  // locate matching item
  Employee Enew= list.getEntry(Eold);
  if(Enew == Employee()) {
    cout << name << " not found..." << endl;
    return;
  }

  cout << "Please enter new sale amount: ";
  cin >> sale;
  Enew+= sale;

  // replace the old item
  if (!list.replace(Enew)) {
    cout << "Error replacing " << name << endl;
  }
}

