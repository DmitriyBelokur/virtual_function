# Виртуальные функции
В этом разделе мы узнаем еще об одном механизме реализации полиморфизма в С++. До этого мы рассматривали так называемый статический полиморфизм. Т.е. мы выполняли перегрузку функций на основе типов, или с помощью шаблонов. В С++ также возможен другой подход к полиморфизму, динамический, который реализуеться спомощью виртуальных функций.
Пример
```cpp
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

```

Мы уже с вами рассматривали этот пример, т.е. у нас есть базовый класс, наследник и наследование между ними открытое. Благодаря открытому наследованию, объект базовго класса может ссылаться на подобъект базового класса в объекте наследника. Но при попытке вызвать метод, который есть и в базовом и производном, то мы вызовем метод базовго класса.
```
void Base::print()
```

Этот подход называеться ранним связыванием. Т.е. это означает что доступность вызова метода проверяетьлся во время компиляции на основе вызываемого объектом типа, а не на основе ссылающегося типа. Т.е. в нашем примере вызов метода `print` будет проверен компилятор на стадии копляции основываясь на тип `Base`, а не на тип Derived на который сылаеться объект базовго класса.

А хотелось бы чтобы имея например указатель или ссылку на базовый класс, динамически вызывать метод объекта на который ссылаеться объект базового класса. И такой подход в С++ реализован посредством виртуальный функций. Идея виртуальных функций есть как раз один интерфейс и разная реализация.
Виртуальные функции позволяют производным классам переопределять(изменять) поведение метода. Производный класс или полностью переопределяет метод базовго класса, или унаследует его поведение. Виртуальные функции реализовывают механизм позднего связывания. Т.е. связывание вызова метода с объектом происходит уже не на этапе компиляции, а на этапе выполнения. Работа виртуальных функций возможна только через ссылки или указатели на базовый класс. Т.е. теперь будет вызываться метод не базового класса, а объекта производного класса на который ссылаеться объект базового класса. Простой пример
```
#include <iostream>

class Car {
  public:
    virtual void Model() {
      std::cout << "This class it's just interface not real type of car" << std::endl;
    }
};

class Ford: public Car{
  public:
    void Model() {
      std::cout << "Ford car" << std::endl;
    }
};

class BMW: public Car{
  public:
    void Model() {
      std::cout << "BMW car" << std::endl;
    }
};

class BMW_M3: public BMW{
  public:
    void Model() {
      std::cout << "BMW M3 car" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
  Ford f;
  Car* car = &f;
  car->Model();

  BMW bmw;
  car = &bmw;
  car->Model();

  car = &bmw_m3;
  car->Model();
  return 0;
}

```

Как видим из примера выше у нас есть три класса, один базовый Car и два производных от базовго Ford и BMW, которые представляют конкретную модель. Класс Car есть некая абстракция. И мы создаем указатель на базовый класс, который сначало ссылаеться на объект класса Ford, а затем на обект класса BMW. Это наследование ничем не отличчаеться от обычных которые мы рассматривали в предущих разделах за исклюсчение ключевого слова `virtual`, этим мы говорим компилятору что этот метод может быть переопределен в производных классах, или унаследован по умолчанию, т.е. компилятор теперь если увидит ссылку или указатель, как в нашем примере, то он не будет статически связывать метод с объектом а будет это выполнять уже динамически на этапе выполнения, т.е. на то что реально ссылаеться наш указатель. Если запустить нашу программу, то мы увидим следующее
```
Ford car
BMW car
BMW M3 car
```

Как видим в отличие от предыдущего примера у нас были вызваны методы уже производных классов на которые указывал указатель базового класса. Это еще называют **динамической диспечеризацией**. Т.е. указатель играет роль некого диспечера и вызвает то на что он сейчас смотрит.

Ключевое слово `virtual` не нужно указывать в классе наследника(хотя можно, иногда даже рекомедуют подеркунуть что этот метод переопределяет баззовый, но начиная с С++11 появилось более лучшее ключевое слово) оно будет автоматически распостраняться на все наследники от этого базовго класса. Как в примере с классом BMW_M3, котрый косвено наследуеться от базового класса.

Но с виртуальными функциями есть одно но. Когда мы рассматривали статическую перегрузка, то она была возможна только если типы параметров функции будут отличаться как по типу так и по количеству. То при использовании динамического полиморфизма, параметры как количествено так и по типам должны быть  одинаковы. Если парметры будут отличаться то мы просто скроем функцию, т.е. будет использоваться скрытие. Пример
```
class Car {
  public:
    virtual void Model() {
      std::cout << "This class it's just interface not real type of car" << std::endl;
    }

    virtual void Year(unsigned year) {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class Ford: public Car{
  public:
    void Model() {
      std::cout << "Ford car" << std::endl;
    }
    void Year(unsigned year) {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW: public Car{
  public:
    void Model() {
      std::cout << "BMW car" << std::endl;
    }
    void Year(int year) {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW_M3: public BMW{
  public:
    void Model() {
      std::cout << "BMW M3 car" << std::endl;
    }
};

int main(int argc, char const *argv[]) {
  Car* car = &f;

  BMW bmw;

  car = &bmw;
  car->Year(100);

  Ford f;
  car = &f;
  car->Year(100);

  return 0;
}
```

Как видим мы добавили в класс Car метод `Year` который принимает безнаковое целое случащие указанием года машины, и переопределили его в классах наследниках, но в классе BMW мы указали другой тип знаковое целое. И если выполнить нашу программу, то получим следующее на экране
```
virtual void Car::Year(unsigned int)
virtual void Ford::Year(unsigned int)
```

Как видим в первом случае мы вызвали метод базового класса, т.к. мы в производном классе скрыли этот метод, а вот во втрором случае если мы видим что мы вызвали переопределенный метод производного класса.

Как видим тут еще есть один момент, то что класс BMW_M3 не переопределяет метод базовго класса, тем самым он унаследует его **поведение по умолчанию**. Как и при обычном наследовании.

До С++11 с таким было тяжело бороться, но начиная с С++11 появилось ключевое слово `override`, которое не только визуально говорит читающему ваш код что вы переопределяете метод базового класса, но еще компилятор ваш выдает ошибку компиляции если вы указали не правильную сигнатуру.
Добавим это ключевое слово к методам `override`, и при попытке компиляции компиялтор нам выдаст ошибку.

```cpp
class Car {
  public:
    virtual void Model() {
      std::cout << "This class it's just interface not real type of car" << std::endl;
    }

    virtual void Year(unsigned year) {
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
};

class BMW: public Car{
  public:
    void Model() {
      std::cout << "BMW car" << std::endl;
    }
    void Year(int year) override {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW_M3: public BMW{
  public:
    void Model() {
      std::cout << "BMW M3 car" << std::endl;
    }
};
```

```
virtual_method.cpp:29:10: error: ‘void BMW::Year(int)’ marked ‘override’, but does not override
     void Year(int year) override {
```

Компилятор вам говорит что вы хотите переопределить метод базового класса, но не переопределяете, так как возможна не верная сигнатура метода. Но не полностью он вам и подсказывает.

Так же в C++11 было добавлено ключевое слово `final` но в контексте уже виртуальных функция. Т.е. применение ключевого слова `final` к виртуальной функции препятствует перекрытию этой
функции в производном классе.
```
Note: provide example
```

Но с витуальнымы функциями есть еще один трабл. Давайте в каждый из наших классов добавим деструктор и прологируем его. И создам объект класса `Ford` на куче посредством указателя на базовый класс.
```cpp
class Car {
  public:
    virtual void Model() {
      std::cout << "This class it's just interface not real type of car" << std::endl;
    }

    virtual void Year(unsigned year) {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
    ~Car() {
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
    ~Ford() {
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
    ~BMW() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

class BMW_M3: public BMW{
  public:
    void Model() {
      std::cout << "BMW M3 car" << std::endl;
    }
    ~BMW_M3() {
      std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

int main(int argc, char const *argv[]) {
  Car* car_dynam = new Ford();
  car_dynam->Model();
  delete car_dynam;
  return 0;
}

```

То на экране мы увидим следующее
```
Ford car
Car::~Car()
```

Т.е. как видно у нас произошла некая утечка, ну фактически она могла произойти если бы производный класс выделял бы память, т.е. вызвался не привычный нам порядок сначало деструктор производного класса, а потом деструктор базового класса. Это все характерно только для динамического создания, т.е. на куче, или при срезке. Таким образом оператор delete выполняет ранее связвание, т.е на этапе компиляции, связав деструктор с базовымклассом. Компилятор даже выдаст вам предупреждение
```
virtual_method.cpp: In function ‘int main(int, const char**)’:
virtual_method.cpp:98:10: warning: deleting object of polymorphic class type ‘Car’ which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor]
   delete car_dynam;

```
Для решения этой проблемы деструкторы тоже делают виртуальными. Тем самым порядок удаления будет правильным.
Давайте перепишем добавив ключевое слово `virtual` к деструкторам.
```
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

int main(int argc, char const *argv[]) {
  Car* car_dynam = new Ford();
  car_dynam->Model();
  delete car_dynam;
  return 0;
}

```

То теперь мы на экране получим следующую вывод
```cpp
Ford car
virtual Ford::~Ford()
virtual Car::~Car()
```

Как видим порядок удаления теперь будет правильным
```
Ford car
virtual Ford::~Ford()
virtual Car::~Car()

```

**Важно** Виртуальных конструкторов не бывает, ну нет в них логики)