#include "common.h"
#include <iostream>

class Base
{
public:
	Base() {}
	virtual ~Base() {}
};

class Father : public Base
{
public:
	Father() {}
	~Father() {}
};

class Child : public Father
{
public:
	Child() {}
	~Child() {}
};

int main()
{
	Base* base = new Child();
	//blocking_timer::main();
}