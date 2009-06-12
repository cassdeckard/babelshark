#include "..\InstructionElement.h"

namespace BabelShark
{


	//virtual function, base definition does nothing.
	//should be implemented by any class inheriting from it.
	void Interpret(char* buffer)
	{

	}

	//virtual function, base definition does nothing.
	//will be used to Display data to the WireShark output
	void Display()
	{

	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	Instruction* GetChild()
	{
		return 0;
	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	void Add(Instruction*)
	{

	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	void Remove(Instruction*)
	{

	}

	//creates a NULL iterator from the object defined in Instruction
	void CreateIterator()
	{
		//_Iter = new NullIterator();
	}
}