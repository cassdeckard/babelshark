// $Id$

#include "UintElement.h"
#include "DataDictionary.h"
#include <sstream>

#include <cstring>

namespace BabelShark
{
    UintElement::UintElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name, variable)
    {
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

	UintElement::~UintElement()
	{

	}

	//Will be used to read in data from packet
    unsigned int UintElement::Interpret(char* buffer)
    {
        std::stringstream result;

        unsigned long long intVal = 0;

        memcpy(&intVal, buffer, MIN(_SizeInBytes, sizeof(intVal)));
        intVal &= _BitMask;
        result << intVal;

        _InterpretedData = result.str();

        // notify subjects of change
        Notify();

        return _Size % 8;
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
