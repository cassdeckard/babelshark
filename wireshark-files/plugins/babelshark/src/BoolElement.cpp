// $Id$

#include "BoolElement.h"

namespace BabelShark
{

    // OLD AND BUSTED
	BoolElement::BoolElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // NEW HOTNESS
    BoolElement::BoolElement(std::string size, std::string name)
        :InstructionElement(size, name)
    {
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

	BoolElement::~BoolElement()
	{

	}

	//Will be used to read in data from packet
    unsigned int BoolElement::Interpret(char* buffer)
    {
        unsigned long intVal = 0;
        unsigned long intMask = _BitMask.to_ulong();

       memcpy(&intVal, buffer, _SizeInBytes);
       intVal &= intMask;
       if (intVal > 0)
       {
          _InterpretedData = "TRUE";
       }
       else
       {
          _InterpretedData = "FALSE";
       }

        // notify subjects of change
        Notify();

        return _Size % 8;
	}

	//will be used to Display data to the WireShark output
	char* BoolElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : " +  _InterpretedData;
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}
}