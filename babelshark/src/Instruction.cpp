// $Id$

#include "..\Instruction.h"

namespace BabelShark
{
	Instruction::Instruction(unsigned int size, char* name)
		:_Size(size), _Name(name)
	{
	}

	Instruction::~Instruction()
	{

	}
	//virtual function, base definition does nothing.
	//should be implemented by any class inheriting from it.
	void Instruction::Interpret(char* buffer)
	{

	}

	//virtual function, base definition does nothing.
	//will be used to Display data to the WireShark output
	char* Instruction::Display()
	{
		return 0;
	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	Instruction* Instruction::GetChild()
	{
		return 0;
	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	void Instruction::Add(Instruction*)
	{

	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	void Instruction::Remove(Instruction*)
	{

	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	void Instruction::CreateIterator()
	{

	}
}