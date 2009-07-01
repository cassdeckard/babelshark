// $Id$

#include "InstructionSet.h"

namespace BabelShark
{

	/**
	 *Constructor
	 */

    // OLD AND BUSTED
	InstructionSet::InstructionSet(unsigned int size, char* name)
		:InstructionNode(size, name)
	{

    }

    // NEW HOTNESS
    InstructionSet::InstructionSet(std::string size, std::string name)
        :InstructionNode(size, name)
    {

    }

	/**
	 *Destructor
	 */
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
    unsigned int InstructionSet::Interpret(char* buffer)
	{
        return 0;
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
		return new ListIterator(this, _List);
	}

    //Override
    unsigned int InstructionSet::GetSizeInBytes()
	{
        unsigned int result = 0;
        int i = 1;

        for(Iterator* it = this->CreateIterator(); ! it->IsDone(); it->Next())
        {
            result += it->CurrentItem()->GetSizeInBytes();
        }

        return result;
    }

    // OVERRIDE
    // For keeping track of subtrees
    unsigned int InstructionSet::NumSubtrees()
    {
        unsigned int result = 0;
        unsigned int size = this->GetSize();


        // for all my children
        for (Iterator* it = this->CreateIterator(); ! it->IsDone(); it->Next())
        {
            result += it->CurrentItem()->NumSubtrees();
        }

        printf("%s has %u arrays with %u subtrees\n",
               this->GetName(),
               size,
               result
              );

        // if this array is > 1 then it has an extra subtree
        // for each element in the array
        if (size > 1)
        {
            return size * result + size + 1;
        }
        else
        {
            return size * result + 1;
        }
    }
}