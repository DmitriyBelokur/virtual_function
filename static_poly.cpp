#include <iostream>

class Base {
  public:
   void print() {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
   }
};

class Derived: public Base {
  public:
   void print() {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
   }
};

int main(int argc, char const *argv[]) {
  Derived d;
  Base& b = d;
  b.print();
  return 0;
}
