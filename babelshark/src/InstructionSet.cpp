#include "..\InstructionSet.h"

namespace BabelShark
{
	//returns the first Child of the InstructionSet list.
	Instruction* InstructionSet::GetChild()
	{
		return 0;
	}

	//Adds a child Instruction to the list.
	void InstructionSet::Add(Instruction*)
	{

	}

	//Removes a child Instruction from the list.
	void InstructionSet::Remove(Instruction*)
	{
		
	}

	//attempts to Interpret the buffer according to the children.
	void InstructionSet::Interpret(char* buffer)
	{
		//while(Iterator)
		{
			//call display on each Instruction pointed to by the Iterator.
		}
	}

	//Creates an iterator used to traverse the direct children.
	void InstructionSet::CreateIterator()
	{
		//InstructionList (i.e. iterator that will traverse down the 1st level of children of this InstructionSet)
		//has not been implemented yet.  When it is, have it be initialized here.
		//_Iter = new InstructionList();
	}
}