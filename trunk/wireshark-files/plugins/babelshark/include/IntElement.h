// $Id$

#ifndef INT_ELEMENT_H
#define INT_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64


namespace BabelShark
{
	/**
		Design Pattern Used: Composite
		Class: IntElement
		Parent: InstructionElement
		One of the Leaf(s) in the Composite Structure.
		Processes Int type elements

		notes: not completed in Phase I.
	*/
	class IntElement: public InstructionElement
	{
		public:
			/** Constructor
				calls parent constructor
				then sets up the bit mask and size in bytes
				*/
			IntElement(unsigned int size, char* name);

			/** Destructor
				Does nothing
				*/
			~IntElement();

			/**	TODO -- Implement this
				Will be used to read in data from packet
				*/
			void Interpret(char* buffer);

			/**	TODO -- Implement this
				will be used to Display data to the WireShark output
				*/
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
		private:
			std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //INT_ELEMENT_H