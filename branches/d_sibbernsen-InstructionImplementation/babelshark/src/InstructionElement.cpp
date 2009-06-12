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

	//Recall we are using the composite pattern
	//Since this is the parent class for all leaf nodes it won't have a child in any case and can always return 0
	Instruction* GetChild()
	{
		return 0;
	}

	//Recall we are using the composite pattern
	//Since this is the parent class for all leaf nodes it won't have the ability to add children
	void Add(Instruction*)
	{

	}

	//Recall we are using the composite pattern
	//Since this is the parent class for all leaf nodes it won't have the ability to remove children
	void Remove(Instruction*)
	{

	}

	//creates a NULL iterator from the object defined in Instruction
	void CreateIterator()
	{
		//_Iter = new NullIterator();
	}
}