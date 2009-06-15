// $Id$

#ifndef INT_ELEMENT_H
#define INT_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64

/*
	Design Pattern Used: Composite
	Class: IntElement
	Parent: InstructionElement
	One of the Leaf(s) in the Composite Structure.
	Processes Int type elements
	
	notes: not completed in Phase I.
*/

namespace BabelShark
{
	class IntElement: public InstructionElement
	{
		public:
			IntElement(unsigned int size, char* name);
			~IntElement();

			//TODO -- Implement this
			//Will be used to read in data from packet
			void Interpret(char* buffer);

			//TODO -- Implement this
			//will be used to Display data to the WireShark output
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
		private:
			std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //INT_ELEMENT_H