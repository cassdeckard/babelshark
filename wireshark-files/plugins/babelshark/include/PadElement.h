// $Id$

#ifndef PAD_ELEMENT_H
#define PAD_ELEMENT_H

#include "InstructionElement.h"



namespace BabelShark
{
	/**
		Design Pattern Used: Composite
		Class: PadElement
		Parent: InstructionElement
		One of the Leaf(s) in the Composite Structure.
		Processes Pad type elements
		*/
	class PadElement: public InstructionElement
	{
		public:
			/** Constructor
				calls parent constructor
				then sets up the size in bytes
				Does not need to setup bitmask since we just throw away the contents
                */
            PadElement(unsigned int size, char* name, std::string variable);
            PadElement(unsigned int size, char* name);

            PadElement(std::string size, std::string name, std::string variable);
            PadElement(std::string size, std::string name); // new constructor

			/** Destructor
				Does nothing
				*/
			~PadElement();

			/** Interpret
				Reads in data from packet
				Throws away the contents, just sets interpreted data to "X bits of padding"
				*/
            unsigned int Interpret(char* buffer);

			/** Display
				Print the name and the interpreted data
				*/
			char* Display();
		private:
	};
}


#endif //PAD_ELEMENT_H