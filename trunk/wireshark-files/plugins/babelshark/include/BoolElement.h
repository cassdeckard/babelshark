// $Id$

#ifndef BOOL_ELEMENT_H
#define BOOL_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64




namespace BabelShark
{
	/**
		Design Pattern Used: Composite
		Class: BoolElement
		Parent: InstructionElement
		One of the Leaf(s) in the Composite Structure.
		Processes Bool type elements
	*/
	class BoolElement: public InstructionElement
	{
		public:

			/** Constructor
				calls parent constructor
				then sets up the bit mask and size in bytes
                */
            BoolElement(unsigned int size, char* name, std::string variable);
			BoolElement(unsigned int size, char* name);

            BoolElement(std::string size, std::string name, std::string variable);
            BoolElement(std::string size, std::string name); // new constructor

			/** Destructor
				Does nothing
				*/
			~BoolElement();

			/** Interpret
				Reads in data from packet
				all 0's is treated as a false, anything else is true
				*/
            unsigned int Interpret(char* buffer);

			/** Display
				Prints out the name and the value (TRUE/FALSE)
				*/
			char* Display();

			std::bitset<BIT_MASK_MAX_SIZE> GetBitMask(){ return _BitMask;}
		private:

            /** members */
            std::bitset<BIT_MASK_MAX_SIZE> _BitMask;
	};
}


#endif //BOOL_ELEMENT_H