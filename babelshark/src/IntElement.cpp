// $Id$

#include "..\IntElement.h"

namespace BabelShark
{

	IntElement::IntElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		_BitMask = SetupBitMask(_Size);
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

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	char* IntElement::Display()
	{
		//Implement me!
		return 0;
	}
}