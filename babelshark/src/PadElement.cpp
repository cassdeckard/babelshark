#include "..\PadElement.h"

namespace BabelShark
{
//Chris's note - Dan had this out there, but I suspect the easiest element to implement will be
//an unsigned int so it might be best to start with that one first.  After we get that working we
//can probably just mimic the same approach in the sibling classes

//If anyone can figure out why the semicolon up on line 2 is required it would be much appreciated

	PadElement::PadElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
	}

	PadElement::~PadElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void PadElement::Interpret(char* buffer)
	{
		_InterpretedData.clear();
		for(size_t i = 0; i < _Size; ++i)
		{
			_InterpretedData += buffer[0];
			buffer++;
		}
		//Implement me!
	}

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	char* PadElement::Display()
	{
		//Implement me!
		return const_cast<char*>(_InterpretedData.c_str());
	}
	
}