#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() { // 仮想デストラクタ
        cout << "Base destructor" << endl;
    }
    virtual void show() {
        cout << "Base class" << endl;
        private_show();
    }
private:
    virtual void private_show() {
        cout << "Base class private" << endl;
    }
};

class Derived : public Base {
public:
    ~Derived() {
        cout << "Derived destructor" << endl;
    }
    void show() override {
        cout << "Derived class" << endl;
        private_show();
    }
private:
    virtual void private_show() {
        cout << "Derived class private" << endl;
    }
};

int main() {
    Base* basePtr = new Derived();
    basePtr->show(); // Derived class
    delete basePtr;
    return 0;
}

