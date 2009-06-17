// $Id$

#include "..\InstructionElement.h"
#include "..\NullIterator.h"

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
	Iterator* InstructionElement::CreateIterator()
	{
		return new NullIterator(this);
	}


    // takes an Input Size and forms a bitmask based on it.
    std::bitset<BIT_MASK_MAX_SIZE> InstructionElement::SetupBitMask(unsigned int val)
    {
        std::bitset<BIT_MASK_MAX_SIZE> result;
        size_t bitMaskIndex = 0;
        while(bitMaskIndex < result.size())
        {
            if(val > 0)
            {
                result.set(bitMaskIndex, 1);
                val--;
            }
            bitMaskIndex++;
        }
        return result;
    }

    // rounds up bit size to byte size
    unsigned int InstructionElement::DetermineSizeInBytes(int bits)
    {
        int sizeInBytes = 0;
        while(bits > 0)
        {
            sizeInBytes++;
            bits -=8;
        }
        return sizeInBytes;
    }


    // OVERRIDE
    unsigned int InstructionElement::NumSubtrees()
    {
        // This is a leaf, so it has no subtrees!
        return 0;
    }

}