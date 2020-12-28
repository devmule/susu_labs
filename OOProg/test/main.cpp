#include <iostream>
using namespace std;

class theBadOne{
public:
    ~theBadOne() {
        throw "Oops!";
    }
};

int main() {
    try {
        theBadOne t;
        throw "I am too old for this";
    }
    catch (const char * text) {
        cout << "screamed:" << text;
    }
    catch (...)
    {
        cout << "someth...";
    }

    return 0;
}
