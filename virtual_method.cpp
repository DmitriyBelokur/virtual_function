#include <iostream>

class Car {
  public:
    virtual void Model() {
      std::cout << "This class it's just interface not real type of car" << std::endl;
    }

    virtual void Year(unsigned year) {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual ~Car() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Ford: public Car{
  public:
    void Model() {
      std::cout << "Ford car" << std::endl;
    }
    void Year(unsigned year) override {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual ~Ford() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW: public Car{
  public:
    void Model() {
      std::cout << "BMW car" << std::endl;
    }
    void Year(unsigned  year) override {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    virtual ~BMW() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW_M3: public BMW{
  public:
    void Model() {
      std::cout << "BMW M3 car" << std::endl;
    }
    virtual ~BMW_M3() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Base {
 public:
   virtual void test(Car& car) {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
   }
};

class Derived1: public Base {
 public:
   void test(Ford& car) {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
   }
};

class Derived2: public Base {
 public:
   void test(BMW& car) {
     std::cout << __PRETTY_FUNCTION__ << std::endl;
   }
};

int main(int argc, char const *argv[]) {
  /*Ford f;
  Car* car = &f;
  car->Model();

  BMW bmw;
  car = &bmw;
  car->Model();
  BMW_M3 bmw_m3;
  car = &bmw_m3;
  car->Model();

  car = &bmw;
  car->Year(100);
  car = &f;
  car->Year(100);

  Derived1 d1;
  Base* base = &d1;

  base->test(bmw);*/

  Car* car_dynam = new Ford();
  car_dynam->Model();
  delete car_dynam;

  std::cout << sizeof(Ford) << std::endl;
  
  return 0;
}
