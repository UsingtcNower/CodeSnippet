#include <string>
#include <new>
#include <iostream>
#include "pattern.h"

using namespace std;

namespace pattern {
// base class ITimeKeeper
class ITimeKeeper {
	public:
		ITimeKeeper() {}
		virtual string getCurrentTime();
		virtual ~ITimeKeeper();
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(ITimeKeeper);
};
string ITimeKeeper::getCurrentTime() {}
ITimeKeeper::~ITimeKeeper() {}

// base class ITimeKeeperFactory
class ITimeKeeperFactory {
	public:
		ITimeKeeperFactory() {}
		virtual ITimeKeeper *create();
		virtual ~ITimeKeeperFactory();
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(ITimeKeeperFactory);

};
ITimeKeeper *ITimeKeeperFactory::create() {}
ITimeKeeperFactory::~ITimeKeeperFactory() {}

// class AtomicClock derived from ITimeKeeper
class AtomicClock : public ITimeKeeper {
	public:
		AtomicClock() {}
		string getCurrentTime() {
			cout<<"Current time in form of Atomic Clock"<<endl;
		}
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(AtomicClock);
};

// class AtomicClockFactory derived from ITimeKeeperFactory
class AtomicClockFactory : public ITimeKeeperFactory {
	public:
		AtomicClockFactory() {}
		ITimeKeeper *create() {
			return new AtomicClock();
		}
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(AtomicClockFactory);
};
}

using namespace pattern;

// keep client code close to change
void client_call(ITimeKeeperFactory factory) {
	ITimeKeeper *time_keeper = factory.create();
	time_keeper->getCurrentTime();
}

int
main() 
{
	AtomicClockFactory factory1;
	client_call(factory1);
}
