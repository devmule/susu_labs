#include <iostream>
#include <deque>

using namespace std;

class EmptyStack : public runtime_error {
public:
    EmptyStack(const string &message = "") : runtime_error(message) {}
};


class Container {
private:
    deque<int_least64_t> c;

public:
    void pushFront(int_least64_t v) {
        c.push_front(v);
    }

    void pushBack(int_least64_t v) {
        c.push_back(v);
    }


    int_least64_t getFront() {
        if (!c.empty()) {
            return c.front();
        } else {
            throw EmptyStack("Empty on getFront()");
        }
    }

    int_least64_t getBack() {
        if (!c.empty()) {
            return c.back();
        } else {
            throw EmptyStack("Empty on getBack()");
        }
    }

    int_least64_t getAverage() {
        if (!c.empty()) {
            return 0;
            // todo !!!!!!!!!
        } else {
            throw EmptyStack("Empty on getAverage()");
        }
    }

    int_least64_t popFront() {
        if (!c.empty()) {
            int_least64_t p = c.front();
            c.pop_front();
            return p;
        } else {
            throw EmptyStack("Empty on popFront()");
        }
    }

    int_least64_t popBack() {
        if (!c.empty()) {
            int_least64_t p = c.back();
            c.pop_back();
            return p;
        } else {
            throw EmptyStack("Empty on popBack()");
        }
    }
};

int main() {
    char c;
    int_least64_t v;
    Container mc;
    while (cin >> c) {
        try {
            switch (c) {
                case 'f':
                    cout << mc.getFront() << "\n";
                    break;
                case 'b':
                    cout << mc.getBack() << "\n";
                    break;
                case 'h':
                    cin >> v;
                    mc.pushFront(v);
                    break;
                case 't':
                    cin >> v;
                    mc.pushBack(v);
                    break;
                case 'a':
                    cout << mc.getAverage() << "\n";
                    break;
                case 'y':
                    cout << mc.popFront() << "\n";
                    break;
                case 'z':
                    cout << mc.popBack() << "\n";
                    break;
            }
        }
        catch (const std::exception &e) {
            cout << e.what() << "\n";
        }
        catch (...) {
            cout << "Dead case\n";
        }
    }
    return 0;
}
