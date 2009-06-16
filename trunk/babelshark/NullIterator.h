// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "Instruction.h"
/*	Class:NullIterator
		An iterator pattern; This represents the iterator to be used for leaf nodes in our
		composite pattern.
*/

namespace BabelShark
{
	class NullIterator : public Iterator
	{
		public:
			NullIterator(Instruction* root);

			~NullIterator();

			void First() {return;}

			Instruction* CurrentItem() {return NULL;}

			void Next() {return;}

			bool IsDone() { return true;}

		protected:
		private:
	};


}

#endif //NULL_ITERATOR_H