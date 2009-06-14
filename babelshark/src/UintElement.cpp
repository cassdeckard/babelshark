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
	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void UintElement::Interpret(char* buffer)
	{
		_InterpretedData.clear();
		_InterpretedData += _Name + " : '";
		unsigned int value = 0;
		for(size_t i = 0; i < _SizeInBytes; ++i)
		{
			static_cast<std::bitset<BIT_MASK_MAX_SIZE>>(buffer[0]) &= _BitMask;
			_InterpretedData += buffer[0];
			buffer++;
		}
		_InterpretedData += "'";
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

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	char* UintElement::Display()
	{
		//Implement me!
		return 0;
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