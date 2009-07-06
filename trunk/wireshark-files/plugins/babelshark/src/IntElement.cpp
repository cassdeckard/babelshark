// $Id$

#include "IntElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    IntElement::IntElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name, variable)
    {
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    IntElement::~IntElement()
    {

    }

	/**Used to read in data from packet*/
    unsigned int IntElement::Interpret(char* buffer)
	{
        std::stringstream result;

        long long intVal = 0;

		// copy data
        memcpy(&intVal, buffer, MIN(_SizeInBytes, sizeof(intVal)));

		// do 2's compliment stuff manually
		// unless this is already a long, then let compiler do it for us
		if ( _SizeInBytes < sizeof(intVal) )
		{
			unsigned long long negative = 0;
			unsigned long long negMask = _BitMask;
			unsigned long long intMask = _BitMask >> 1;
			negMask &= ~intMask;

			negative = intVal & negMask; // get sign bit
			intVal &= intMask;           // strip sign bit from number
			if (negative) intVal -= negMask;
		}

		// convert to string
        result << intVal;
        _InterpretedData = result.str();

        // notify subjects of change
        Notify();

        return _Size % 8;
	}

	/**Used to Display data to the WireShark output*/
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
