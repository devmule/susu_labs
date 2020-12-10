#include <iostream>
#include <string>
#include "Employees.h"

void print_list(const list<VirtualEmployee *> &employeeList) {
    for (VirtualEmployee *e : employeeList)
        e->print();
}

list<VirtualEmployee *> read_file(const string &filename) {
    string temp, type;
    int employee_count = 7;
    int manager_count = 8;
    int tsc_count = 10;
    int consultant_count = 8;
    vector<string> params;
    ifstream file;
    list<VirtualEmployee *> empl;

    file.open(filename);
    while (file >> temp) {
        int count = 0;

        type = temp;
        if (temp == "Employee" || temp == "Secretary")count = employee_count;
        else if (temp == "Manager" || temp == "Director")count = manager_count;
        else if (temp == "Consultant")count = consultant_count;
        else count = tsc_count;

        for (int i = 0; i < count; i++) {
            file >> temp;
            params.push_back(temp);
        }

        if (type == "Employee") {
            Employee *e = new Employee(params[0], params[1], params[2],
                                       Date(stoi(params[3]), stoi(params[4]),
                                            stoi(params[5])), stoi(params[6]));
            empl.push_back(e);
        } else if (type == "Secretary") {
            Secretary *s = new Secretary(params[0], params[1], params[2],
                                         Date(stoi(params[3]), stoi(params[4]),
                                              stoi(params[5])), stoi(params[6]));
            empl.push_back(s);
        } else if (type == "Manager") {
            Manager *m = new Manager(params[0], params[1], params[2],
                                     Date(stoi(params[3]),
                                          stoi(params[4]), stoi(params[5])),
                                     stoi(params[6]), stoi(params[7]));
            empl.push_back(m);
        } else if (type == "Director") {
            Director *d = new Director(params[0], params[1], params[2],
                                       Date(stoi(params[3]), stoi(params[4]),
                                            stoi(params[5])), stoi(params[6]),
                                       stoi(params[7]));
            empl.push_back(d);
        } else if (type == "Consultant") {
            Consultant *c = new Consultant(params[0], params[1],
                                           Date(stoi(params[2]), stoi(params[3]),
                                                stoi(params[4])), Date(stoi(params[5]),
                                                                       stoi(params[6]), stoi(params[7])));
            empl.push_back(c);
        } else {
            Tsec *ts = new Tsec(params[0], params[1], params[2], stoi(params[3]),
                                Date(stoi(params[4]), stoi(params[5]),
                                     stoi(params[6])), Date(stoi(params[7]),
                                                            stoi(params[8]), stoi(params[9])));
            empl.push_back(ts);
        }

        params.clear();
    }
    file.close();
    return empl;
}

int main() {
    list<VirtualEmployee *> employeeList = read_file("..\\input.txt");
    print_list(employeeList);

    cout << "Employees: " << Employee::total << endl
         << "Managers: " << Manager::total << endl
         << "Secretaries: " << Secretary::total << endl
         << "Directors: " << Director::total << endl
         << "Temporary: " << Temporary::total << endl
         << "Consultants: " << Consultant::total << endl
         << "TSecs: " << Tsec::total << endl;

    return 0;
}