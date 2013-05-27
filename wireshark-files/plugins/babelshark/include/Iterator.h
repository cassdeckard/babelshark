// $Id$

#ifndef ITERATOR_H
#define ITERATOR_H

#include "Instruction.h"

namespace BabelShark
{
    class Instruction; // forward declaration
	/**		Class:Iterator
			An iterator pattern; This represents the  abstractIterator to be extended for specific iterators we need

			Currently we don't have a preorder/in order/post order traversal, but this could be done
			Also we could use a template to make this more generic, but didn't feel that was necessary at this time
			given the time constraints
	*/
	class Iterator
	{
		public:

			/** Constructor
				Just assigns the root note member variable
				*/
			Iterator(Instruction* root);

			/**	Destructor
				Empty, Does nothing
				*/
			~Iterator();

			/**	First (virtual)
				Does nothing since the children will implement this
				*/
			virtual void First();

			/**	Currentitem(virtual)
				returns null since the children will implement this
				*/
            virtual Instruction* CurrentItem();

			/**	Next (virtual)
				Does nothing since the children will implement this
				*/
            virtual void Next();

			/**	IsDone(virtual)
				returns true always since the children will implement this
				*/
            virtual bool IsDone();

		protected:
			/**	member variable */
			Instruction* _rootNode;
		private:
	};
}

#endif