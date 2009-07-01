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
            AsciiElement(unsigned int size, char* name, std::string variable);
            AsciiElement(unsigned int size, char* name);

            AsciiElement(std::string size, std::string name, std::string variable);
            AsciiElement(std::string size, std::string name); // new constructor

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
            std::string AsciiElement::Printable(char inChar);
	};
}


#endif //ASCII_ELEMENT_H