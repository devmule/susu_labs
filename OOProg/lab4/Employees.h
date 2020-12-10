#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <fstream>
#include "Date.h"

using namespace std;


class VirtualEmployee {
public:
    string type;
    short int level = 0;

    virtual void print() = 0;
};

class Employee : virtual public VirtualEmployee {
public:
    static int total;

    string first_name, surname;
    string patronymic_letter;
    Date hiring_date;
    short int department;

    Employee(string fn, string sn, string pl, Date hd, short int dt);

    ~Employee();

    void print() override;
};

class Manager : public Employee {
public:
    static int total;

    Manager(string fn, string sn, string pl, Date hd, short int dt, short int lvl);

    ~Manager();
};

class Secretary : public Employee {
public:
    static int total;

    Secretary(string fn, string sn, string pl, Date hd, short int dt);

    ~Secretary();
};

class Director : public Manager {
public:
    static int total;

    Director(string fn, string sn, string pl, Date hd, short int dt, short int lvl);

    ~Director();
};

class Temporary : virtual public VirtualEmployee {
public:
    static int total;

    string first_name, surname;
    Date begin, end;

    Temporary(string fn, string sn, Date bg, Date ed);

    ~Temporary();

    void print() override;
};

class Consultant : public Temporary {
public:
    static int total;

    Consultant(string fn, string sn, Date bg, Date ed);

    ~Consultant();
};

class Tsec : public Secretary, public Temporary {
public:
    static int total;

    Tsec(string fn, string sn, string pl, short int dt, Date bg, Date ed);

    void print() override;

    ~Tsec();
};