// $Id: InstructionTree.h 37 2009-06-14 15:22:55Z thegordonemail $

#ifndef INSTRUCTION_TREE_H
#define INSTRUCTION_TREE_H

#include <string>
#include <vector>
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

}

#endif //INSTRUCTION_TREE_H