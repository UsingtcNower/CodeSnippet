#include "pattern.h"
#include <iostream>
#include <set>
#include <string>

using namespace std;

namespace pattern{
// class declaration
class Observer; // forward declaration

class Subject {
	public:
		Subject();
		virtual ~Subject() = 0;
		void addObserver(Observer* obr);
		void removeObserver(Observer* obr);
	protected:
		void fire();
	private:
		set<Observer*> observers;
};

class Observer {
	public:
		Observer(Subject*);
		virtual ~Observer();
		virtual void response() = 0;
		void removeSubject(Subject* subj);
	private:
		Subject* m_subj;
};

// class definition
Subject::Subject() {}

Subject::~Subject() {}

void Subject::addObserver(Observer* obr) {
	observers.insert(obr);
}

void Subject::removeObserver(Observer* obr) {
	observers.erase(obr);
}

void Subject::fire() {
	for(auto it:observers) { 
		it->response();
	}
}

Observer::~Observer() {
	if(m_subj!=NULL)
		m_subj->removeObserver(this);
}

Observer::Observer(Subject* subj) : m_subj(subj){
	if(m_subj!=NULL)
		m_subj->addObserver(this);
}

// derived classes
class Cat : public Subject {
	public:
		Cat(string name);
		~Cat() {}
		void Cry();
	private:
		string m_name;
};

Cat::Cat(string name) : Subject() {
	m_name=name;
}

void Cat::Cry() {
	cout<<"cat "<<m_name<<" cryed."<<endl;
	fire();
}

class Mouse : public Observer{
	public:
		Mouse(string name, Subject* subj);
		~Mouse() {}
		void response();
	private:
		string m_name;
};

Mouse::Mouse(string name, Subject* subj) : Observer(subj), m_name(name) {}

void Mouse::response() {
	cout<<"Mouse "<<m_name<<" escaped!"<<endl;
}

class Master : public Observer {
	public:
		Master(string name, Subject* subj);
		~Master();
		void response();
	private:
		string m_name;
};

Master::Master(string name, Subject* subj) : Observer(subj), m_name(name) {}

Master::~Master() {}

void Master::response() {
	cout<<"Master "<<m_name<<" waken up!"<<endl;
}

} // namespace pattern

int
main()
{
	using namespace pattern;

	Cat cat1("cat1");
	Mouse mouse1("mouse1", &cat1);
	Cat cat2("cat2");
	Mouse mouse2("mouse2", &cat2);
	Master master2("cat2's master", &cat2);
	Master* master1 = new Master("cat1's master", &cat1);
	delete master1;
	Mouse* mouse3 =  new Mouse("mouse3", NULL);
	delete mouse3;

	cat1.Cry();
	cout<<endl;

	cat2.Cry();
}
