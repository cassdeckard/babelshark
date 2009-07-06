// $Id$

#ifndef INT_ELEMENT_H
#define INT_ELEMENT_H

#include "InstructionElement.h"

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
            IntElement(unsigned int size, char* name, std::string variable);
			IntElement(unsigned int size, char* name);

            IntElement(std::string size, std::string name, std::string variable);
            IntElement(std::string size, std::string name); // new constructor

			/** Destructor
				Does nothing
				*/
			~IntElement();

			/**	Interpret
			  *	Reads in data from packet in one of two ways
			  * If its a long it lets the compiler handle the two's compliment
			  * If not it is manually done
			  */
            unsigned int Interpret(char* buffer);

			/**	Display
			  *	Prints out the name and value
			  */
			char* Display();

		private:
			unsigned long long _BitMask;
	};
}


#endif //INT_ELEMENT_H
