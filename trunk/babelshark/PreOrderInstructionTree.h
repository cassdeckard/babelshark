// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef PREORDER_INSTRUCTION_TREE_H
#define PREORDER_INSTRUCTION_TREE_H

#include <string>
#include <vector>
#include "Instruction.h"
#include "InstructionTree.h"

/*
	Class:PreOrderInstructionTree
		An iterator pattern; This represents the iterator to be used for leaf nodes in our
		composite pattern.
*/



namespace BabelShark
{
	typedef std::vector<InstructionTree*> InstructionTreeCollection;
	class PreOrderInstructionTree : public InstructionTree
	{
		public:
			PreOrderInstructionTree(Instruction* root);

			~PreOrderInstructionTree();

			void First();

			Instruction* CurrentItem();

			void Next();

			bool IsDone();



		protected:
			InstructionTreeCollection* _childIterators;

	
		private:


	};


}

#endif //PREORDER_INSTRUCTION_TREE_H