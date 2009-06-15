// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef NULL_INSTRUCTION_TREE_H
#define NULL_INSTRUCTION_TREE_H

#include <string>
#include "Instruction.h"
#include "InstructionTree.h"

/*
	Class:NullInstructionTree
		An iterator pattern; This represents the iterator to be used for leaf nodes in our
		composite pattern.
*/



namespace BabelShark
{
	class NullInstructionTree : public InstructionTree
	{
		public:
			NullInstructionTree(Instruction* root);

			~NullInstructionTree();

			void First() {return;}

			Instruction* CurrentItem() {return _rootNode;}

			void Next() {return;}

			bool IsDone() { return true;}



		protected:

	
		private:

			Instruction* _rootNode;

	};


}

#endif //NULL_INSTRUCTION_TREE_H