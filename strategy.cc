#include "pattern.h"
#include <iostream>

namespace pattern {
using namespace std;

class TestBase {
public:
	TestBase() {}
	virtual ~TestBase() {}
	virtual void start() {
		cout<<"start to test testbase."<<endl;
	}
};

TestBase defaultTestBase;

class TestHarness {
	TestBase* testbase;
	DISALLOW_EVIL_CONSTRUCTORS(TestHarness);
public:
	explicit TestHarness(TestBase* ptestbase=&defaultTestBase)
		: testbase(ptestbase) {}
	void runTest() {
		testbase->start();
	}

	void setTestee(TestBase* another_test) {
		testbase=another_test;
	}
};

class HeavyTest : public TestBase {
public:
	HeavyTest() {}
	~HeavyTest() {}
	void start() {
		cout<<"start to test heavytest."<<endl;
	}
};

class CustomTest : public TestBase {
public:
	CustomTest() {}
	~CustomTest() {}
	void start() {
		cout<<"start to test customtest."<<endl;
	}
};
}	// namespace pattern

using namespace pattern;
int 
main() 
{
	TestHarness testbed;
	testbed.runTest();

	HeavyTest heavy_test;
	testbed.setTestee(&heavy_test);
	testbed.runTest();

	CustomTest custom_test;
	testbed.setTestee(&custom_test);
	testbed.runTest();
}
