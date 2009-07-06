// $Id$

#include "PadElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    PadElement::PadElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name, variable)
    {
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

	PadElement::~PadElement()
	{

	}

	//Will be used to read in data from packet
    unsigned int PadElement::Interpret(char* buffer)
    {
        std::stringstream result;
        result << "(" << _Size << " bits of padding)";
        _InterpretedData = result.str();

        // notify subjects of change
        Notify();

        return _Size % 8;
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
