// $Id$

#ifndef ASCII_ELEMENT_H
#define ASCII_ELEMENT_H

#include "InstructionElement.h"

/*
	Design Pattern Used: Composite
	Class: AsciiElement
	Parent: InstructionElement
	One of the Leaf(s) in the Composite Structure.
	Processes Ascii type elements
*/



namespace BabelShark
{
	class AsciiElement: public InstructionElement
	{
		public:
			AsciiElement(unsigned int size, char* name);
			~AsciiElement();

			//Will be used to read in data from packet
			void Interpret(char* buffer);

			//will be used to Display data to the WireShark output
			char* Display();
		private:
            // Checks to see if a character is printable.  if it is, it returns
			//a string with that character stored in it.
			//if not, it returns a string with a single space in it.
            std::string AsciiElement::Printable(char inChar);
	};
}


#endif //ASCII_ELEMENT_H