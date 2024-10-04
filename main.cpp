#include <iostream>
#include <string>

// Наследование - инструмент языка для расширения 
// функционала класса через сужение его специализации
// 
// При наследовании мы строим новый класс через повторное использование 
// кода, написанного ранее класса
// при этом происходит измененение типа доступа компонентов 
// родительского класса иходя из зоны видимости 
// и типа наследования.
// 
// что наследуется:
//  - поля и методы класса
//  - операторы если они определены как методы класса
//  - статические поля и методы
// 
// что не наследуется:
//  - дружественные функции
//  - дружественные классы 
//  - определенные как внешние функции операторы
// 
// Наличие наследования в коде - единственный способ
// включения динамического полиморфизма
//

class Base
{
public:
	Base() = default;
	Base(int all);
	Base(int a, int b);
	~Base();

	int getA()const;
	int getB()const;

	void setA(int a);
	void setB(int b);

	void Clear();
	int FullSum()const;
	bool operator==(const Base& other)const;

protected:
	void ClearA();
	void ClearB();

	int b;

private:
	int a;
};

Base::Base(int all)
{
	this->a = all;
	this->b = all;
}
Base::Base(int a, int b)
{
	this->a = a;
	this->b = b;
}
Base::~Base()
{
}

int Base::getA() const
{
	return this->a;
}
int Base::getB() const
{
	return this->b;
}

void Base::setA(int a)
{
	this->a = a;
}
void Base::setB(int b)
{
	this->b = b;
}

void Base::Clear()
{
	this->ClearA();
	this->ClearB();
}
int Base::FullSum() const
{
	return this->a + this->b;
}
bool Base::operator==(const Base& other)const
{
	return this->a == other.a && this->b == other.b;
}

void Base::ClearA()
{
	this->a = 0;
}
void Base::ClearB()
{
	this->b = 0;
}

bool operator!=(const Base& a, const Base& b)
{
	return !(a == b);
}


//  - при публичном наследовании клиентам класса-наследника
// доступны все публичные методы класса-родителя
//  - защищенные методы и поля класса-родителя становятся
// защищенными методами и полями класса-наследника
//  - приватные методы и поля класса-родителя становятся
// недоступными для прямого взаимодейтсвия 
// компонентами класса-наследника
//

class Derived : public Base
{
public:
	Derived() = default;
	Derived(int a, int b, int c) : Base(a, b), c(c) {} // поля a, b мы заставляем инициализировать конструктор родителя
	~Derived();

	int getC()const;
	void setC(int c);

	int FullSum()const;

	void Clear();

protected:
	void ClearC();

private:
	int c;
};

Derived::~Derived()
{
}

int Derived::getC() const
{
	return this->c;
}
void Derived::setC(int c)
{
	this->c = c;
}

int Derived::FullSum() const
{
	return this->getA() + this->b + this->c;
}

void Derived::Clear()
{
	Base::Clear();
	this->ClearC();
}

void Derived::ClearC()
{
	this->c = 0;
}


int main()
{
	system("color 0F");

	Base obj1;
	Base obj2(1, 3);

	obj1 == obj2;
	obj1 != obj2;
	
//	obj1 == 2; // программа сама создоаст объект Base вместо 2 и сравнит
//	2 == obj1; // компилятор делает вид что понятия не имеет что и с чем сравнивать

	obj1 != 2;
	2 != obj1;
	//   |
	//   V
	// когда оператор создан как внешняя функция
	// компилятор в любом случае сравнение проведет

	Derived objDer1(4, 3, 7);
	/*objDer1.setA(4);
	objDer1.setB(7);
	objDer1.setC(4);*/
	std::cout << objDer1.FullSum() << '\n';
	objDer1 == obj2;


	std::cout << obj2.FullSum() << '\n';
	obj2.Clear();
	std::cout << obj2.FullSum() << '\n';

	std::cout << objDer1.FullSum() << '\n';
	obj2.Clear();
	std::cout << objDer1.FullSum() << '\n';

	return 0;
}