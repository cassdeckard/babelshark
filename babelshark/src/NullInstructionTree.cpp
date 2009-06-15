// $Id: NullInstructionTree.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "..\NullInstructionTree.h"

namespace BabelShark
{
	NullInstructionTree::NullInstructionTree(Instruction* root)
		: InstructionTree(root)
	{

	}


	NullInstructionTree::~NullInstructionTree(){
		return;
	}

}