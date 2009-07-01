// $Id$

#include "IntElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{

    // OLD AND BUSTED
    IntElement::IntElement(unsigned int size, char* name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "IntElement(" << size << ", " << name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // OLD AND BUSTED
    IntElement::IntElement(unsigned int size, char* name)
        :InstructionElement(size, name)
    {
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // NEW HOTNESS
    IntElement::IntElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "IntElement(" << _Size << ", " << _Name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    // NEW HOTNESS
    IntElement::IntElement(std::string size, std::string name)
        :InstructionElement(size, name)
    {
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    IntElement::~IntElement()
    {

    }

	//TODO -- Implement this
	//Will be used to read in data from packet
    unsigned int IntElement::Interpret(char* buffer)
	{
        std::stringstream result;

        long intVal = 0;

		// copy data
        memcpy(&intVal, buffer, _SizeInBytes);

		// do 2's compliment stuff manually
		// unless this is already a long, then let compiler do it for us
		if ( _Size < 32 )
		{
			unsigned long negative = 0;
			unsigned long negMask = _BitMask.to_ulong();
			unsigned long intMask = _BitMask.to_ulong() >> 1;
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
