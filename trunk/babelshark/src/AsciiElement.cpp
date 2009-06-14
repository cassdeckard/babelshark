// $Id$

#include "..\AsciiElement.h"

namespace BabelShark
{
//Chris's note - Dan had this out there, but I suspect the easiest element to implement will be
//an unsigned int so it might be best to start with that one first.  After we get that working we
//can probably just mimic the same approach in the sibling classes

//If anyone can figure out why the semicolon up on line 2 is required it would be much appreciated

	AsciiElement::AsciiElement(unsigned int size, char* name)
		:InstructionElement(size, name)
    {
        _SizeInBytes = size;
	}

	AsciiElement::~AsciiElement()
	{

	}

	//Will be used to read in data from packet
	void AsciiElement::Interpret(char* buffer)
	{
		_InterpretedData.clear();
        _InterpretedData += _Name + " : '";
		for(size_t i = 0; i < _Size; ++i)
		{
			_InterpretedData += buffer[0];
			buffer++;
        }
        _InterpretedData += "'";
	}

	//will be used to Display data to the WireShark output
	char* AsciiElement::Display()
	{
		return const_cast<char*>(_InterpretedData.c_str());
	}

}