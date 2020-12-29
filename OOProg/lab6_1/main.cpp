#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <algorithm>
using namespace::std;

typedef long long ll;

class EmptyStack : public runtime_error
{
public:
    EmptyStack(const string & message =""):runtime_error(message) {}
};


class StackMin
{
    vector < pair <ll, ll> > data;

public:
    StackMin():data{}
    {}

    void push(ll v)
    {
        if (data.size()) data.push_back({ v, min(v, data.rbegin()->second) });
        else data.push_back({ v,v });
    }

    ll top() {
        if (data.size()) return data.rbegin()->first;
        else throw EmptyStack("Empty on top()");
    }

    ll pop() {
        if (data.size()) {
            ll a = data.rbegin()->first;
            data.pop_back();
            return a;
        } else throw EmptyStack("Empty on pop()");
    }

    ll getmin() {
        if (data.size())  return data.rbegin()->second;
        else throw EmptyStack("Empty on getmin()");
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