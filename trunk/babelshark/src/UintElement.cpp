// $Id$

#include "..\UintElement.h"

namespace BabelShark
{

	UintElement::UintElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		_BitMask = SetupBitMask(_Size);
		_SizeInBytes = DetermineSizeInBytes(size);
	}

	UintElement::~UintElement()
	{

	}

	//Will be used to read in data from packet
	void UintElement::Interpret(char* buffer)
    {
        char          tempDisplay[255];
        unsigned long intVal = 0;
        unsigned long intMask = _BitMask.to_ulong();
		_InterpretedData.clear();
		_InterpretedData += _Name + " : ";

       memcpy(&intVal, buffer, _SizeInBytes);
       sprintf(tempDisplay, "%u", intVal & intMask);

       _InterpretedData += tempDisplay;
	}

	//will be used to Display data to the WireShark output
	char* UintElement::Display()
    {
        return const_cast<char*>(_InterpretedData.c_str());
	}

}