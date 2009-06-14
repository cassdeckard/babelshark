// $Id$

#include "..\InstructionSet.h"

namespace BabelShark
{

	InstructionSet::InstructionSet(unsigned int size, char* name)
		:Instruction(size, name)
	{

	}

	InstructionSet::~InstructionSet()
	{
		CreateIterator();

	}
	//returns the first Child of the InstructionSet list.
	Instruction* InstructionSet::GetChild()
	{
		return 0;
	}

	//Adds a child Instruction to the list.
	void InstructionSet::Add(Instruction* instruction)
	{
		_List.push_back(instruction);
		_SizeInBytes += instruction->GetSizeInBytes();
	}



	//attempts to Interpret the buffer according to the children.
	void InstructionSet::Interpret(char* buffer)
	{
		CreateIterator();

		for(_ListIter; _ListIter != _List.end(); ++_ListIter)
		{
			(*_ListIter)->Interpret(buffer);
		}
	}

	//Creates an iterator used to traverse the direct children.
	void InstructionSet::CreateIterator()
	{
		_ListIter = _List.begin();
	}
}