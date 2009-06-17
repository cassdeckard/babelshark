// $Id$

#ifndef BOOL_ELEMENT_H
#define BOOL_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64

/*
	Design Pattern Used: Composite
	Class: BoolElement
	Parent: InstructionElement
	One of the Leaf(s) in the Composite Structure.
	Processes Bool type elements
*/



namespace BabelShark
{
	class BoolElement: public InstructionElement
	{
		public:
			BoolElement(unsigned int size, char* name);
			~BoolElement();

			//used to read in data from packet
			void Interpret(char* buffer);

			//used to Display data to the WireShark output
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
		private:

            // members
            std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //BOOL_ELEMENT_H