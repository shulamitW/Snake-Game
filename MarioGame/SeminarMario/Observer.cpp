#include "Observer.h"

void Subject::Register(IObserverPtr o)
{
	_observers.push_back(o);
}

void Subject::Notify(Event const& e) // רץ על כל הנרשמים לאירוע ומעדכן אותן
{
	for (auto& o : _observers)
		o->onNotify(e);//מעדכן את האירוע 
}

#define COMPARE_EXPLICIT(a,b) if ((a)<(b)) return true; else if ((a)>(b)) return false;
bool Event::operator<(Event const& other) const
{
	COMPARE_EXPLICIT(sender, other.sender);
	COMPARE_EXPLICIT(code, other.code);
	COMPARE_EXPLICIT(type, other.type);
	return false;
}
