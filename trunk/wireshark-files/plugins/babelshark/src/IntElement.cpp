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
        //Implement me!
        _InterpretedData = "(not implemented yet)";

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