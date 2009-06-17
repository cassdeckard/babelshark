// $Id$

#include "Instruction.h"
#include "NullIterator.h"

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
	Iterator* Instruction::CreateIterator()
	{
		return new NullIterator(this);
	}

    //virtual function, overridden by InstructionElement
    // For keeping track of subtrees
    unsigned int Instruction::NumSubtrees()
    {
        unsigned int result = 0; // don't count this! It might not be a subtree

        // for all my children
        for (Iterator* it = this->CreateIterator(); ! it->IsDone(); it->Next())
        {
            result += it->CurrentItem()->NumSubtrees();
        }

        return result;
    }
}