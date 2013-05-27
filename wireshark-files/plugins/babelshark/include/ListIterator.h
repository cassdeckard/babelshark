// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef LIST_ITERATOR_H
#define LIST_ITERATOR_H

#include "Instruction.h"

namespace BabelShark
{
	/**		Class:ListIterator
			An iterator pattern; This represents the ListIterator (one of the concrete iterators)
			to be used for composite nodes in our composite pattern.

			This also acts as a concrete adapter (in the adapter pattern)
			It is adapting the stl::iterator to a concrete iterator in the iterator pattern
	*/
    typedef std::vector<Instruction*> InstructionCollection;
	class ListIterator : public Iterator
	{
		public:
			/** Constructor
				Calls parent then sets the member variable _List and initializes the stl::iterator for it
				*/
			ListIterator(Instruction* root, InstructionCollection list);

			/**	Destructor
				Empty, Does nothing
				*/
			~ListIterator();

			/** First
				Calls begin() on the stl::iterator to 'initialize' it
				*/
			void First();

			/** CurrentItem
				Returns the current item by dereferencing it since that's how the stl does it
				*/
			Instruction* CurrentItem();

			/** Next
				'Increments' the counter which is the stl way of advancing to the next element in the list
				*/
			void Next();

			/** IsDone
				Checks if the address the pointer is pointing to is the same address occupied by the last element of
				the list (indicating we can't advance it any further and thus are done
				*/
			bool IsDone();

		protected:
		private:
			InstructionCollection _List;
			InstructionCollection::iterator _ListIter;

	};


}

#endif //LIST_ITERATOR_H