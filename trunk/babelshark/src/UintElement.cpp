// $Id$

#include "..\UintElement.h"
#include <sstream>

namespace BabelShark
{

	UintElement::UintElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		_BitMask = SetupBitMask(_Size);
		_SizeInBytes = DetermineSizeInBytes(size);
	}

	UintElement::~UintElement()
	{

	}

	//Will be used to read in data from packet
	void UintElement::Interpret(char* buffer)
    {
        std::stringstream result;

        unsigned long intVal = 0;
        unsigned long intMask = _BitMask.to_ulong();

        memcpy(&intVal, buffer, _SizeInBytes);
        intVal &= intMask;
        result << intVal;

        _InterpretedData = result.str();
	}

	//will be used to Display data to the WireShark output
	char* UintElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : " +  _InterpretedData;
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}

}