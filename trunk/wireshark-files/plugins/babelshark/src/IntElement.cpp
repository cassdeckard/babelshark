// $Id$

#include "IntElement.h"

namespace BabelShark
{

	IntElement::IntElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
	}

	IntElement::~IntElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet
	void IntElement::Interpret(char* buffer)
	{
        //Implement me!
        _InterpretedData = "(not implemented yet)";
	}

	//will be used to Display data to the WireShark output
	char* IntElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : " +  _InterpretedData;
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}
}