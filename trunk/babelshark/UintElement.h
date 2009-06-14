#ifndef UINT_ELEMENT_H
#define UINT_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64

namespace BabelShark
{
	class UintElement: public InstructionElement
	{
		public:
			UintElement(unsigned int size, char* name);
			~UintElement();
			
			//TODO -- Implement this
			//Will be used to read in data from packet (I think??)
			void Interpret(char* buffer);
			
			//TODO -- Implement this
			//will be used to Display data to the WireShark output
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
		private:
			//takes our Input Size and forms the _BitMask based on it.
			unsigned int DetermineSizeInBytes(int bits);
			void SetupBitMask(unsigned int val);
			std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
			std::string _InterpretedData;
	};
}


#endif //UINT_ELEMENT_H