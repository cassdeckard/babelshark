// $Id $

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>

namespace BabelShark
{

    class Subject
	{
		public:
            Subject() { }
            ~Subject() { }

            void Attach(Observer* observer);

            void Detach(Observer* observer);

            void Notify();

        protected:

            std::list<Observer*> _Observers;

	};
}

#endif // SUBJECT_H
