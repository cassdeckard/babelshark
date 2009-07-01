// $Id $

#ifndef OBSERVER_H
#define OBSERVER_H

namespace BabelShark
{
    class Subject; // forward declaration

    /** TypeDefinition is the abstract base class for user-defined types.
      */
	class Observer
	{
        public:

           Observer() { }

           ~Observer() { }

           virtual void Update(Subject* subject) { }

		protected:

        private:
	};

}

#endif // OBSERVER_H
