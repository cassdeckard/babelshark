#include "..\IntElement.h"

namespace BabelShark
{

	IntElement::IntElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		SetupBitMask(_Size);
	}

	IntElement::~IntElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void IntElement::Interpret(char* buffer)
	{
		//Implement me!
	}

	void IntElement::SetupBitMask(unsigned int val)
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
	char* IntElement::Display()
	{
		//Implement me!
		return 0;
	}
}