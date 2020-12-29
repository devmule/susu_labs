#include <iostream>

using namespace std;

class Lamp {
    bool isOn;
public :
    Lamp() : isOn(false) {}
    operator bool() const { return isOn; }
    bool on() { return isOn = true; }
    bool off() { return isOn = false; }
    bool change() { return isOn = !isOn; }
};


int main() {
    char c;
    Lamp l;
    while (cin >> c) {
        switch (c) {
            case 'u' :
                cout << l.on() << "\n";
                break;
            case 'd' :
                cout << l.off() << "\n";
                break;
            case 'c' :
                cout << l.change() << "\n";
                break;
            case 'g' :
                cout << (bool) l << "\n";
                break;
        }
    }
    return 0;
}
