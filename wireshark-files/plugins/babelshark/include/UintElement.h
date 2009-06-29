// $Id$

#ifndef UINT_ELEMENT_H
#define UINT_ELEMENT_H

#include "InstructionElement.h"


namespace BabelShark
{
	/**
		Design Pattern Used: Composite
		Class: UintElement
		Parent: InstructionElement
		One of the Leaf(s) in the Composite Structure.
		Processes Uint type elements
	*/
	class UintElement: public InstructionElement
	{
		public:
			/** Constructor
				calls parent constructor
				then sets up the bit mask and size in bytes
                */
            UintElement(unsigned int size, char* name, std::string variable);
			UintElement(unsigned int size, char* name);

			/** Destructor
				Does nothing
				*/
			~UintElement();

			/** Interpret
				Reads in data from packet
				This one gets a little complex
				converts the bitmask to an unsigned long and then does a bitwise and
				then it uses a stream to convert that to a character value
				*/
            unsigned int Interpret(char* buffer);

			/** Display
				Prints out the name and the value as an unsigned int
				*/
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
        private:

            // members
			std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //UINT_ELEMENT_H