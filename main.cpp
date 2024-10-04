#include <iostream>
#include <string>

// ������������ - ���������� ����� ��� ���������� 
// ����������� ������ ����� ������� ��� �������������
// 
// ��� ������������ �� ������ ����� ����� ����� ��������� ������������� 
// ����, ����������� ����� ������
// ��� ���� ���������� ����������� ���� ������� ����������� 
// ������������� ������ ����� �� ���� ��������� 
// � ���� ������������.
// 
// ��� �����������:
//  - ���� � ������ ������
//  - ��������� ���� ��� ���������� ��� ������ ������
//  - ����������� ���� � ������
// 
// ��� �� �����������:
//  - ������������� �������
//  - ������������� ������ 
//  - ������������ ��� ������� ������� ���������
// 
// ������� ������������ � ���� - ������������ ������
// ��������� ������������� ������������
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

Base::Base()
{
}
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


//  - ��� ��������� ������������ �������� ������-����������
// �������� ��� ��������� ������ ������-��������
//  - ���������� ������ � ���� ������-�������� ����������
// ����������� �������� � ������ ������-����������
//  - ��������� ������ � ���� ������-�������� ����������
// ������������ ��� ������� �������������� 
// ������������ ������-����������
//

class Derived : public Base
{
public:
	Derived();
	~Derived();

	int getC()const;
	void setC(int c);

	int FullSum()const;

private:
	int c;
};

Derived::Derived()
{
}
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
	return this->a + this->b + this->c;
}


int main()
{
	Base obj1;
	Base obj2(1, 3);

	obj1 == obj2;
	obj1 != obj2;
	
//	obj1 == 2; // ��������� ���� �������� ������ Base ������ 2 � �������
//	2 == obj1; //  ���������� ������ ��� ��� ������� �� ����� ��� � � ��� ����������

	obj1 != 2;
	2 != obj1;
	//   |
	//   V
	// ����� �������� ������ ��� ������� �������
	// ���������� � ����� ������ ��������� ��������

	Derived objDer1;
	objDer1.setA(4);
	objDer1.setB(7);
	std::cout << objDer1.FullSum();

	return 0;
}