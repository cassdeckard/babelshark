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

	}
	//returns the first Child of the InstructionSet list.
	Instruction* InstructionSet::GetChild()
    {
        CreateIterator();
        return _ListIter[0];
	}

	//Adds a child Instruction to the list.
	void InstructionSet::Add(Instruction* instruction)
	{
		_List.push_back(instruction);
		//_SizeInBytes += instruction->GetSizeInBytes();
	}



	//attempts to Interpret the buffer according to the children.
	void InstructionSet::Interpret(char* buffer)
	{
	}


    //will be used to Display data to the WireShark output
    char* InstructionSet::Display()
    {
        static char* result;
        result = new char[_Name.length() + 1];
        memcpy(result, _Name.c_str(), _Name.length());
        result[_Name.length()] = 0; // null terminator
        return result;
    }

	//Creates an iterator used to traverse the direct children.
	Iterator* InstructionSet::CreateIterator()
	{
		return &ListIterator(this, _List);
	}

    //Override
    unsigned int InstructionSet::GetSizeInBytes() 
	{
        unsigned int result = 0;

        CreateIterator();
        for(_ListIter; _ListIter != _List.end(); ++_ListIter)
        {
            result += (*_ListIter)->GetSizeInBytes();
        }

        return result;
    }
}