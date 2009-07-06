// $Id $

#ifndef OBSERVER_H
#define OBSERVER_H

namespace BabelShark
{
    class Subject; // forward declaration

    /** Observer is another abstract class for the observer pattern
      * It represents the base class for any number of concrete observers
      * Currently these are planned to be instruction sizes or aliased instructions
      * In the future could be more uses
      */
	class Observer
	{
        public:

		/** Empty constructor since its an abstract class
		  */
           Observer() { }

		/** Empty destructor since its an abstract class
		  */
           ~Observer() { }

		/** This is where the actual work of the pattern will take place
		  * Still an abstract class though, so it will happen at the concrete observer level.
		  */
           virtual void Update(Subject* subject) { }

		protected:

        private:
	};

}

#endif // OBSERVER_H
