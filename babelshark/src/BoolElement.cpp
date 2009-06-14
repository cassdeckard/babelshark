// $Id$

#include "..\BoolElement.h"

namespace BabelShark
{

	BoolElement::BoolElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
        _BitMask = SetupBitMask(_Size);
        _SizeInBytes = DetermineSizeInBytes(size);
	}

	BoolElement::~BoolElement()
	{

	}

	//Will be used to read in data from packet (I think??)
	void BoolElement::Interpret(char* buffer)
    {
        unsigned long intVal = 0;
        unsigned long intMask = _BitMask.to_ulong();
        _InterpretedData.clear();
        _InterpretedData += _Name + " : ";

       memcpy(&intVal, buffer, _SizeInBytes);
       intVal &= intMask;
       if (intVal > 0)
       {
          _InterpretedData += "TRUE";
       }
       else
       {
          _InterpretedData += "FALSE";
       }
	}

	//will be used to Display data to the WireShark output
	char* BoolElement::Display()
    {
        return const_cast<char*>(_InterpretedData.c_str());
	}
}