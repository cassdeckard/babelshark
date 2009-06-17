// $Id$

#include "FloatElement.h"

namespace BabelShark
{

	FloatElement::FloatElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
        SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
	}

	FloatElement::~FloatElement()
	{

	}
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void FloatElement::Interpret(char* buffer)
	{
		//Implement me!
        _InterpretedData = "(not implemented yet)";
	}

	void FloatElement::SetupBitMask(unsigned int val)
	{
		size_t bitMaskIndex = 0;
		while(bitMaskIndex < _BitMask.size())
		{
			if(val > 0)
			{
				_BitMask.set(bitMaskIndex, 1);
				val--;
			}
			bitMaskIndex++;
		}
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