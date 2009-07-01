// $Id$

#include "PadElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{

    // OLD AND BUSTED
    PadElement::PadElement(unsigned int size, char* name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "PadElement(" << size << ", " << name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // OLD AND BUSTED
    PadElement::PadElement(unsigned int size, char* name)
        :InstructionElement(size, name)
    {
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // NEW HOTNESS
    PadElement::PadElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "PadElement(" << _Size << ", " << _Name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    // NEW HOTNESS
    PadElement::PadElement(std::string size, std::string name)
        :InstructionElement(size, name)
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