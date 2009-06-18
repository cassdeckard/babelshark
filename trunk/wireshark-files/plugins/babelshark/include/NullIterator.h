// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef NULL_ITERATOR_H
#define NULL_ITERATOR_H

#include "Instruction.h"

namespace BabelShark
{
	/*	Class:NullIterator
			An iterator pattern; This represents the iterator to be used for leaf nodes in our
			composite pattern (one of the concreteIterators in the pattern)
	*/
	class NullIterator : public Iterator
	{
		public:
			/** Constructor
				Just calls parent
				*/
			NullIterator(Instruction* root);

			/** Destructor
				Does nothing
				*/
			~NullIterator();

			/** First
				Does nothing
				*/
			void First() {return;}

			/** CurrentItem
				returns root node
				*/
			Instruction* CurrentItem() {return _rootNode}

			/** Next
				Does nothing since we can't advance
				*/
			void Next() {return;}

			/** IsDone
				returns true always (since there's only one element we're always done!
				*/
			bool IsDone() { return true;}

		protected:
		private:
	};


}

#endif //NULL_ITERATOR_H