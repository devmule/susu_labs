#include <iostream>

using namespace std;

class Elevator {
private:
    long long minStage;
    long long maxStage;
    long long homeStage;
    long long stage;

public:
    Elevator(long long minStage, long long maxStage, long long homeStage) {
        this->minStage = minStage;
        this->maxStage = maxStage;
        this->homeStage = this->stage = homeStage;
    }

    long long goHome() {
        this->stage = this->homeStage;
        return this->stage;
    }

    long long goStage(long long goStage) {
        if (goStage >= this->minStage && goStage <= this->maxStage) this->stage = goStage;
        return this->stage;
    }

    long long getCurStage() {
        return this->stage;
    }

    Elevator &operator++() {
        if (this->stage < this->maxStage) this->stage++;
        return *this;
    }

    Elevator &operator--() {
        if (this->stage > this->minStage) this->stage--;
        return *this;
    }
};

ostream &operator<<(std::ostream &os, Elevator el) {
    os << el.getCurStage();
    return os;
}


int main() {
    char c;
    long long minStage, maxStage, homeStage, stage;
    cin >> minStage >> maxStage >> homeStage;
    Elevator el(minStage, maxStage, homeStage);
    while (cin >> c) {
        switch (c) {
            case 'i':
                cout << ++el << "\n";
                break;
            case 'd':
                cout << --el << "\n";
                break;
            case 'g':
                cin >> stage;
                cout << el.goStage(stage) << "\n";
                break;
            case 's':
                cout << el.getCurStage() << "\n";
                break;
            case 'h':
                cout << el.goHome() << "\n";
                break;
        }
    }
    return 0;
}

