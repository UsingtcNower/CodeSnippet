#include "pattern.h"
#include <iostream>
#include <memory>

namespace pattern {
using namespace std;

void defaultTest(void) {
	cout<<"start to test testbase."<<endl;
}

class TestHarness {
	typedef function<void (void)> TestFunc;
	TestFunc testFunc;
	DISALLOW_EVIL_CONSTRUCTORS(TestHarness);
public:
	explicit TestHarness(TestFunc tf=defaultTest)
		: testFunc(tf) {}
	void runTest() const {
		testFunc();
	}

	void setTestee(TestFunc another_test) {
		testFunc=another_test;
	}
};

class HeavyTest {
public:
	HeavyTest() {}
	~HeavyTest() {}
	void start() {
		cout<<"start to test heavytest."<<endl;
	}
};

struct CustomTest {
	void operator() (void) const {
		cout<<"start to test customtest."<<endl;
	}
};
}	// namespace pattern

using namespace pattern;
int 
main() 
{
	TestHarness testbed(defaultTest);
	testbed.runTest();

	testbed.setTestee(CustomTest());
	testbed.runTest();

	HeavyTest heavy_test;
	testbed.setTestee(bind(&HeavyTest::start, heavy_test));
	testbed.runTest();
}
