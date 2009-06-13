#include "..\UintElement.h"

namespace BabelShark
{

	UintElement::UintElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		SetupBitMask(_Size);
	}

	UintElement::~UintElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void UintElement::Interpret(char* buffer)
	{
		//Implement me!
	}

	void UintElement::SetupBitMask(unsigned int val)
	{
		size_t bitMaskIndex = 0;
		while(bitMaskIndex < _BitMask.size())
		{
			if(val > 0)
			{
				_BitMask.set(bitMaskIndex, 1);
				val--;
			}
			bitMaskIndex++;
		}
	}

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	char* UintElement::Display()
	{
		//Implement me!
		return 0;
	}
/*
	//Since this is a leaf node it won't have a child
	Instruction* UintElement::GetChild()
	{
		return 0;
	}

	//Since this is a leaf node it won't have a child
	void UintElement::Add(Instruction*)
	{
		return;
	}

	//Since this is a leaf node it won't have a child
	void UintElement::Remove(Instruction*)
	{
		return;
	}
*/
	//TODO
	//I don't understand why this is returning a null iterator, but parent class did. :)
	//creates a NULL iterator from the object defined in Instruction
	void UintElement::CreateIterator()
	{
		//_Iter = new NullIterator();
		return;
	}
}