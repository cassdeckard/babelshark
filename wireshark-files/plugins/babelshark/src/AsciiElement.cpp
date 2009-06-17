// $Id$

#include "AsciiElement.h"

namespace BabelShark
{
//Chris's note - Dan had this out there, but I suspect the easiest element to implement will be
//an unsigned int so it might be best to start with that one first.  After we get that working we
//can probably just mimic the same approach in the sibling classes

//If anyone can figure out why the semicolon up on line 2 is required it would be much appreciated

	AsciiElement::AsciiElement(unsigned int size, char* name)
		:InstructionElement(size, name)
    {
        _SizeInBytes = size;
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


	void AsciiElement::Interpret(char* buffer)
    {
		_InterpretedData.clear();

        for(size_t i = 0; i < _Size && buffer[i] != 0; ++i)
		{
			_InterpretedData += Printable(buffer[i]);
        }

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