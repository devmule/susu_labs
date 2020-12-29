#include <iostream>

using namespace std;


class PriorityQueue2Min {
};


int main() {
    char c;
    int_least64_t v;
    PriorityQueue2Min mpq;
    while (cin >> c) {
        try {
            switch (c) {
                case 'f':
                    cout << mpq.firstMin() << "\n";
                    break;
                case 's':
                    cout << mpq.secondMin() << "\n";
                    break;
                case 'a':
                    cin >> v;
                    mpq.insert(v);
                    break;
                case 'p':
                    cout << mpq.extractMin() << "\n";
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
