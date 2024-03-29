// $Id$

#ifndef ASCII_ELEMENT_H
#define ASCII_ELEMENT_H

#include "InstructionElement.h"




namespace BabelShark
{
/**
 * \class AsciiElement
 * Parent: InstructionElement
 * Design Pattern Used: Composite
 * One of the Leaf(s) in the Composite Structure.
 * Processes Ascii type elements
 */
	class AsciiElement: public InstructionElement
	{
		public:
			/**
			 * Constructor
             */
            AsciiElement(std::string size, std::string name, std::string variable = "");

			/**
			 * Destructor
			 */
			~AsciiElement();

			/**
			 * Interpret function for Ascii;
			 * will just read in the correct number of characters
			 */
            unsigned int Interpret(char* buffer);

			/**
			 * Display function for Ascii;
			 * will just print the bytes as a character
			 */
			char* Display();
		private:
            /**
			 * Checks to see if a character is printable.  if it is, it returns
			 * a string with that character stored in it.
			 * if not, it returns a string with a single space in it.
			 */
            std::string Printable(char inChar);
	};
}


#endif //ASCII_ELEMENT_H
