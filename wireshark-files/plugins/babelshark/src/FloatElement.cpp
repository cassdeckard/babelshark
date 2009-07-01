// $Id$

#include "FloatElement.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{

    // OLD AND BUSTED
    FloatElement::FloatElement(unsigned int size, char* name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "FloatElement(" << size << ", " << name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);

        // Round up size
        if (_Size <= 32)
        {
        	_Size = 32;
        }
        else
        {
        	_Size = 64;
        }

        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // OLD AND BUSTED
    FloatElement::FloatElement(unsigned int size, char* name)
        :InstructionElement(size, name)
    {
        // Round up size
        if (_Size <= 32)
        {
        	_Size = 32;
        }
        else
        {
        	_Size = 64;
        }

        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
    }

    // NEW HOTNESS
    FloatElement::FloatElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name)
    {
        std::stringstream ss;
        ss << "FloatElement(" << _Size << ", " << _Name << ", " << variable.c_str() << ")\n";
        printf(ss.str().c_str());
        DataDictionary::Instance()->AddVariable(variable, this);

        // Round up size
        if (_Size <= 32)
        {
        	_Size = 32;
        }
        else
        {
        	_Size = 64;
        }

        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

    // NEW HOTNESS
    FloatElement::FloatElement(std::string size, std::string name)
        :InstructionElement(size, name)
    {
        // Round up size
        if (_Size <= 32)
        {
        	_Size = 32;
        }
        else
        {
        	_Size = 64;
        }

        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(_Size);
    }

	FloatElement::~FloatElement()
	{

	}

	//Will be used to read in data from packet (I think??)
    unsigned int FloatElement::Interpret(char* buffer)
	{
        std::stringstream result;

        if ( _SizeInBytes == sizeof(float) )
        {
        	float floatVal = 0;
            memcpy(&floatVal, buffer, sizeof(float));
            result << floatVal;
        }
        else if ( _SizeInBytes == sizeof(double) )
        {
        	double doubleVal = 0;
            memcpy(&doubleVal, buffer, sizeof(double));
            result << doubleVal;
        }
        else
        {
        	result << "(ERROR)";
        }

        _InterpretedData = result.str();

        // notify subjects of change
        Notify();

        return 0;
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
