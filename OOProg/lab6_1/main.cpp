#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

class StackMin {
private:
    list<long long> vec;

    static bool comp(const long long *lhs, const long long *rhs) {
        return lhs < rhs;
    }

public:
    void push(long long s) {
        vec.push_front(s);
    }

    long long top() {
        if (vec.empty()) {
            throw exception("Empty on top()");
        } else {
            return vec.front();
        }
    }

    long long pop() {
        if (vec.empty()) {
            throw exception("Empty on pop()");
        } else {
            long long top = vec.front();
            vec.pop_front();
            return top;
        }
    }

    long long getmin() {
        if (vec.empty()) {
            throw exception("Empty on getmin()");
        } else {
            long long min = vec.front();
            for (long long val : vec) if (val < min) min = val;
            return min;
        }
    }
};


int main() {
    char c;
    long long v;
    StackMin st;
    while (cin >> c) {
        try {
            switch (c) {
                case 't':
                    cout << st.top() << "\n";
                    break;
                case 'p':
                    cout << st.pop() << "\n";
                    break;
                case 'a':
                    cin >> v;
                    st.push(v);
                    break;
                case 'm':
                    cout << st.getmin() << "\n";
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