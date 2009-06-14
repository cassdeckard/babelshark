// $Id$

#include "..\UintElement.h"

namespace BabelShark
{

	UintElement::UintElement(unsigned int size, char* name)
		:InstructionElement(size, name)
	{
		SetupBitMask(_Size);
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
       sprintf(tempDisplay, "%u\0", intVal & intMask);

       _InterpretedData += tempDisplay;
	}

	void UintElement::SetupBitMask(unsigned int val)
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
	char* UintElement::Display()
    {
        return const_cast<char*>(_InterpretedData.c_str());
	}

	unsigned int UintElement::DetermineSizeInBytes(int bits)
	{
		int sizeInBytes = 0;
		while(bits > 0)
		{
			sizeInBytes++;
			bits -=8;
		}
		return sizeInBytes;
	}
}