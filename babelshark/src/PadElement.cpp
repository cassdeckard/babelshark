// $Id$

#include "..\PadElement.h"
#include <sstream>

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
        std::stringstream result;
        result << "(" << _Size << " bits of padding)";
        _InterpretedData = result.str();
	}

	//will be used to Display data to the WireShark output
	char* PadElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : " +  _InterpretedData;
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}

}