#include <string>
#include <new>
#include <memory>
#include <iostream>
#include "pattern.h"

using namespace std;

namespace pattern {
// base class ITimeKeeper
class ITimeKeeper {
	public:
		ITimeKeeper() {}
		virtual void printCurrentTime() = 0;
		virtual ~ITimeKeeper();
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(ITimeKeeper);
};
void ITimeKeeper::printCurrentTime() {}
ITimeKeeper::~ITimeKeeper() {}

// base class ITimeKeeperFactory
class ITimeKeeperFactory {
	public:
		ITimeKeeperFactory() {}
		virtual shared_ptr<ITimeKeeper> create() const = 0;
		virtual ~ITimeKeeperFactory();
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(ITimeKeeperFactory);

};
shared_ptr<ITimeKeeper> ITimeKeeperFactory::create() const {}
ITimeKeeperFactory::~ITimeKeeperFactory() {}

// class AtomicClock derived from ITimeKeeper
class AtomicClock : public ITimeKeeper {
	public:
		AtomicClock() {}
		void printCurrentTime() {
			cout<<"Current time in form of Atomic Clock"<<endl;
		}
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(AtomicClock);
};

// class AtomicClockFactory derived from ITimeKeeperFactory
class AtomicClockFactory : public ITimeKeeperFactory {
	public:
		AtomicClockFactory() {}
		shared_ptr<ITimeKeeper> create() const {
			shared_ptr<ITimeKeeper> pITimeKeeper(new AtomicClock()); 
			return pITimeKeeper;
		}
	private:
		//DISALLOW_EVIL_CONSTRUCTORS(AtomicClockFactory);
};
}

using namespace pattern;

// keep client code close to change
void client_call(const ITimeKeeperFactory& factory) {
	shared_ptr<ITimeKeeper> time_keeper = factory.create();
	time_keeper->printCurrentTime();
}

int
main() 
{
	AtomicClockFactory factory1;
	client_call(factory1);
}
