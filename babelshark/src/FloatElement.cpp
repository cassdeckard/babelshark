#include "..\FloatElement.h"

namespace BabelShark
{

	FloatElement::FloatElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		SetupBitMask(_Size);
	}

	FloatElement::~FloatElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void FloatElement::Interpret(char* buffer)
	{
		//Implement me!
	}

	void FloatElement::SetupBitMask(unsigned int val)
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
	char* FloatElement::Display()
	{
		//Implement me!
		return 0;
	}
}