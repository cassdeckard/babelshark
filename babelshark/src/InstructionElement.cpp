// $Id$

#include "..\InstructionElement.h"

namespace BabelShark
{
	InstructionElement::InstructionElement(unsigned int size, char* name)
		:Instruction(size, name)
	{

	}
	InstructionElement::~InstructionElement()
	{

	}

	//virtual function, base definition does nothing.
	//should be implemented by any class inheriting from it.
	void InstructionElement::Interpret(char* buffer)
	{

	}

	//virtual function, base definition does nothing.
	//will be used to Display data to the WireShark output
	char* InstructionElement::Display()
	{
		return 0;
	}

	//Recall we are using the composite pattern
	//Since this is the parent class for all leaf nodes it won't have a child in any case and can always return 0
	Instruction* InstructionElement::GetChild()
	{
		return 0;
	}


	//creates a NULL iterator from the object defined in Instruction
	void InstructionElement::CreateIterator()
	{
		//_Iter = new NullIterator();
	}
}