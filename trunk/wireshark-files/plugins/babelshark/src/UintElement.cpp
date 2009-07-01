// $Id$

#include "UintElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    // OLD AND BUSTED
    UintElement::UintElement(unsigned int size, char* name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "UintElement(" << size << ", " << name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // OLD AND BUSTED
	UintElement::UintElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		_BitMask = SetupBitMask(_Size);
		_SizeInBytes = DetermineSizeInBytes(size);
	}

    // NEW HOTNESS
    UintElement::UintElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "UintElement(" << _Size << ", " << _Name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    // NEW HOTNESS
    UintElement::UintElement(std::string size, std::string name)
        :InstructionElement(size, name)
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

        unsigned long intVal = 0;
        unsigned long intMask = _BitMask.to_ulong();

        memcpy(&intVal, buffer, _SizeInBytes);
        intVal &= intMask;
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