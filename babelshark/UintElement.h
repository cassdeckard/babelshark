// $Id$

#ifndef UINT_ELEMENT_H
#define UINT_ELEMENT_H

#include "InstructionElement.h"

namespace BabelShark
{
	class UintElement: public InstructionElement
	{
		public:
			UintElement(unsigned int size, char* name);
			~UintElement();

			//Will be used to read in data from packet
			void Interpret(char* buffer);

			//will be used to Display data to the WireShark output
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
        private:

            // members
			std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //UINT_ELEMENT_H