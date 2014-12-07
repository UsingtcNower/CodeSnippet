// template method
#include "pattern.h"
#include <iostream>

using namespace std;

namespace pattern {
class TestBase {
	public:
		virtual ~TestBase() {}

		void test() {
			do_something_before_test();
			do_test();
			do_something_after_test();
		}

		virtual void do_test() {
			cout<<"base testing..."<<endl;
		}

		void do_something_before_test() {}
		void do_something_after_test() {}
};

class HeavyTest : public TestBase {
	public:
		void do_test() {
			cout<<"heavy testing..."<<endl;
		}
};

class CustomTest : public TestBase {
	public:
		void do_test() {
			cout<<"custom testing..."<<endl;
		}
};

} //namespace pattern

using namespace pattern;

int
main()
{
	HeavyTest heavy_test;
	heavy_test.test();

	CustomTest custom_test;
	custom_test.test();
}
