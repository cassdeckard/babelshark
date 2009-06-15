// $Id: InstructionTree.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "..\InstructionTree.h"

namespace BabelShark
{
	InstructionTree::InstructionTree(Instruction* root){
		_root = root;
		_iterators = std::stack<InstructionTree*>();
		return;
	}

	InstructionTree::~InstructionTree(){
		return;
	}


}