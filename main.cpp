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
// 
// static
//  - Внутри функции меняет место хранения переменной 
// перемещает ее из стека вызовов в глобальные переменные
//  - Если применено к свободным функциям или глобальным переменным
// запрещает их вызов из сторонних кодовых файлов
//  - Примененное к методам или полям класса, позволяет работать
// с данными полями и классами без создания объектов
// 
// 
// Правила работы статических методов:
// 
//	  1 - Их можно вызывать в любой момент работы программы
//        даже если объекта класса для вызова нет под рукой
// 
//    2 - Доступность для использования зависит только 
//        от категории доступа (public, private, protected)
// 
//    3 - В теле статического метода можно вызывать только
//        другие статические методы класса и обращаться только к 
//        статическим полям своего класса.
// 
//    4 - На работу с внешними элементами (аргументами, 
//        глобальными переменными, внешними классами и 
//        функциями) ограничений нет.
// 
// 
// types of inheritance:
//    public, private, protected
// 
// Наследованием которое используется в проектах по умолчанию 
// является публичное. Оно позволяет включать полиморфизм и 
// именно поэтому чаще всего используется.
// 
// Если при наследовании не указать тип, то по умолчанию компилятор 
// будет считать что наследование было приватным.
// При приватном наследовании меняется доступность родительских
// компонентов переходящих в класс наследник и теряется 
// возможность применять полиморфизм.
// 
// При защищенном наследовании те же проблемы но изменение доступа
// к родительским полям и методам происходит по другим правилам
// 
// 
//   base_access | public    | protected | private     <- (типы наследования)
//   ------------|-----------|-----------|---------
//   public      | public    | protected | private 
//   protected   | protected | protected | private 
//   private     | unreach   | unreach   | unreach
//      ^
//      |  
//   (переменные)
// 
//   было------->| стало
// 
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

	// объявление того что в состав класса
	// входит статическая переменная  
	// вместе с телом класса будет жить в header-файлах
	//
	static int st;

	static void PrintWord()
	{
		std::cout << "word\n";
	}

protected:
	void ClearA();
	void ClearB();

	int b;

private:
	int a;
};

// В этот момент мы определили чем является переменная.
// Определения статических переменных нужно оставлять 
// ТОЛЬКО в файлах cpp
//
int Base::st = 0;

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



	Base::st = 0;

	// статические методы доступны для работы как от имени объектов класса, так 
	// и без них при обращении через имя класса
	//
	Base obj1;
	obj1.PrintWord();
	Base::PrintWord();

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
	objDer1.PrintWord();
	Derived::PrintWord();

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