// Singleton pattern code snippet 
#include "pattern.h"
#include <iostream>
#include <memory>

namespace pattern{

class SingletonCounter {
private:
	SingletonCounter():cnt(0) {}
	static std::shared_ptr<SingletonCounter> instance;
	int cnt;
	DISALLOW_EVIL_CONSTRUCTORS(SingletonCounter);
public:
	static SingletonCounter *getInstance() {
		return instance.get();
	}

	void increase(int x) {
		cnt += x;
	}

	int getCount() {
		return cnt;
	}
};
std::shared_ptr<SingletonCounter> SingletonCounter::instance(new SingletonCounter());

}	// namespace pattern


int
main()
{
	pattern::SingletonCounter *user1 = pattern::SingletonCounter::getInstance();
	user1->increase(1);
	std::cout<<user1->getCount()<<std::endl;
	pattern::SingletonCounter *user2 = pattern::SingletonCounter::getInstance();
	user2->increase(2);
	std::cout<<user2->getCount()<<std::endl;
}
