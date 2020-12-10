#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include "Employees.h"

using namespace std;

Employee::Employee(string fn, string sn, string pl, Date hd, short int dt) {
    first_name = fn;
    surname = sn;
    patronymic_letter = pl;
    hiring_date = hd;
    department = dt;
    type = "Employee";
    total++;
}

Employee::~Employee() { total--; };

void Employee::print() {
    string full_name = first_name + " " + patronymic_letter + ". " + surname;
    cout << type << ": " << full_name << endl
         << "Hiring date: " << hiring_date << endl
         << "Department: " << department << endl;
    if (level > 0) cout << "Level: " << level << endl << endl;
    else cout << endl;
}

Manager::Manager(string fn, string sn, string pl, Date hd, short int dt, short int lvl) : Employee(fn, sn, pl, hd, dt) {
    level = lvl;
    type = "Manager";
    total++;
}

Manager::~Manager() { total--; };

Secretary::Secretary(string fn, string sn, string pl, Date hd, short int dt) : Employee(fn, sn, pl, hd, dt) {
    type = "Secretary";
    total++;
}

Secretary::~Secretary() { total--; };

Director::Director(string fn, string sn, string pl, Date hd, short int dt, short int lvl) : Manager(fn, sn, pl, hd, dt,
                                                                                                    lvl) {
    type = "Director";
    total++;
}

Director::~Director() { total--; };

Temporary::Temporary(string fn, string sn, Date bg, Date ed) {
    first_name = fn;
    surname = sn;
    begin = bg;
    end = ed;
    type = "Temporary";
    total++;
}

Temporary::~Temporary() { total--; };

void Temporary::print() {
    string full_name = first_name + " " + surname;
    cout << type << ": " << full_name << endl
         << "Begin date: " << begin << endl
         << "End date: " << end << endl << endl;
}

Consultant::Consultant(string fn, string sn, Date bg, Date ed) : Temporary(fn, sn, bg, ed) {
    type = "Consultant";
    total++;
}

Consultant::~Consultant() { total--; };

Tsec::Tsec(string fn, string sn, string pl, short int dt, Date bg, Date ed) :
        Secretary(fn, sn, pl, bg, dt), Temporary(fn, sn, bg, ed) {
    type = "Tsec";
    total++;
}

Tsec::~Tsec() { total--; }

void Tsec::print() {
    Temporary::print();
}

int Employee::total = 0;
int Manager::total = 0;
int Secretary::total = 0;
int Director::total = 0;
int Temporary::total = 0;
int Consultant::total = 0;
int Tsec::total = 0;