// $Id$

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
        _SizeInBytes = DetermineSizeInBytes(size);
	}

	PadElement::~PadElement()
	{

	}

	//Will be used to read in data from packet
	void PadElement::Interpret(char* buffer)
    {
        char tempDisplay[255];
        _InterpretedData.clear();
        _InterpretedData += _Name + " : ";

        sprintf(tempDisplay, "(%i bits of padding)", _Size);
        _InterpretedData += tempDisplay;
	}

	//will be used to Display data to the WireShark output
	char* PadElement::Display()
	{
		return const_cast<char*>(_InterpretedData.c_str());
	}

}