// $Id$

#include "..\AsciiElement.h"

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

    // TODO: DESCRIPTION
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

	//Will be used to read in data from packet
	void AsciiElement::Interpret(char* buffer)
    {

		_InterpretedData.clear();
        _InterpretedData += _Name + " : '";

		for(size_t i = 0; i < _Size; ++i)
		{
			_InterpretedData += Printable(buffer[i]);
        }

        _InterpretedData +="'";
	}

	//will be used to Display data to the WireShark output
	char* AsciiElement::Display()
	{
		return const_cast<char*>(_InterpretedData.c_str());
	}

}