// $Id$

#include "FloatElement.h"

namespace BabelShark
{

    // OLD AND BUSTED
	FloatElement::FloatElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // NEW HOTNESS
    FloatElement::FloatElement(std::string size, std::string name)
        :InstructionElement(size, name)
    {
        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

	FloatElement::~FloatElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
    unsigned int FloatElement::Interpret(char* buffer)
	{
		//Implement me!
        _InterpretedData = "(not implemented yet)";

        // notify subjects of change
        Notify();

        return _Size % 8;
	}

	//will be used to Display data to the WireShark output
	char* FloatElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : " +  _InterpretedData;
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}
}