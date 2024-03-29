// $Id$

#include "AsciiElement.h"
#include "DataDictionary.h"

#include <cstring>

namespace BabelShark
{
    AsciiElement::AsciiElement(std::string size, std::string name, std::string variable)
        :InstructionElement(size, name, variable)
    {
        _SizeInBytes = _Size;
    }

    AsciiElement::~AsciiElement()
    {

    }

    // Verifies that the character we're printing is printable in Ascii
    std::string AsciiElement::Printable(char inChar)
    {
        std::string result;
        // 0x20 - 0x7f is the valid range of printable characters
        if ( (inChar >= 0x20) && (inChar < 0x7f) )
        {
            result = inChar;
        }
        else
        {
            result = " "; // return space for nonprintable characters
        }

        if ( inChar == '%' ) result += '%'; // because printf is used to display these,
                                            // must double up on %s

        return result;
    }


    unsigned int AsciiElement::Interpret(char* buffer)
    {
		_InterpretedData.clear();

        for(size_t i = 0; i < _Size && buffer[i] != 0; ++i)
		{
			_InterpretedData += Printable(buffer[i]);
        }

        // notify subjects of change
        Notify();

        return 0;
	}

	char* AsciiElement::Display()
    {
        static char* result;
        std::string resultStr = _Name + " : '" +  _InterpretedData + "'";
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
	}

}
