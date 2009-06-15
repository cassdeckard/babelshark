// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef INSTRUCTION_TREE_H
#define INSTRUCTION_TREE_H

#include <string>
#include <vector>
#include <stack>
#include "Instruction.h"
#include "InstructionSet.h"

/*
	Class:InstructionTree
		An iterator pattern; since the packets are ordered (at least for the time being) in a 
		very specific way that corresponds with the language definition it is currently only
		allowing Pre Order Iteration.  If in the future this decision was ever in need
		of changing this class could be extended to support other traversal order.
*/



namespace BabelShark
{
	class InstructionTree
	{
		public:
			InstructionTree(Instruction* root);

			~InstructionTree();

			virtual void First(){ }

			virtual Instruction* CurrentItem(){return 0;} 

			virtual void Next(){ }

			virtual bool IsDone(){return true;}


		protected:
			Instruction* _root;
			std::stack<InstructionCollection::iterator*> _iterators;
	
		private:


	};


}

#endif //INSTRUCTION_TREE_H