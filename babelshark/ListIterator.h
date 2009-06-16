// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "Instruction.h"
/*	Class:ListIterator
		An iterator pattern; This represents the iterator to be used for leaf nodes in our
		composite pattern.
*/

namespace BabelShark
{
	class ListIterator : public Iterator
	{
		public:
			ListIterator(Instruction* root, InstructionCollection list);

			~ListIterator();

			void First();

			Instruction* CurrentItem();

			void Next();

			bool IsDone();

		protected:
		private:
			InstructionCollection _List;
			InstructionCollection::iterator _ListIter;

	};


}

#endif //LIST_ITERATOR_H