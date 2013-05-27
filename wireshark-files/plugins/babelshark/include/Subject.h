// $Id $

#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <list>

namespace BabelShark
{

    /** Subject is base class for the observer pattern
      * At this point it doesn't seem like any of the child subjects would need to change this functionality
      * as its pretty standard, but the possibility exists.
      */
    class Subject
	{
		public:
		    /** Empty constructor since no construction needed.
		      */
            Subject() { }
		    /** Empty destructor since no construction needed.
		      */
            ~Subject() { }

		    /** Adds the observer to the list of observers so when the notify method is called we know they want
		      * to be notified
		      */
            void Attach(Observer* observer);

		    /** Removes the observer to the list of observers so when the notify method is called we know they
		      * no longer care about changes to the subject.
		      */
            void Detach(Observer* observer);

		    /** Perform the highly important job of notifying the observers in the list of observers.
		      */
            void Notify();

        protected:

		    /** Objects who care when the subject changes.
		      */
            std::list<Observer*> _Observers;

	};
}

#endif // SUBJECT_H
