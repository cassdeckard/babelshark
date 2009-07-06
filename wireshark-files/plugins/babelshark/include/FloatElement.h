// $Id$

#ifndef FLOAT_ELEMENT_H
#define FLOAT_ELEMENT_H

#include "InstructionElement.h"

namespace BabelShark
{
	/**
	  *	\class FloatElement
	  *	Design Pattern Used: Composite
	  *	Parent: InstructionElement
	  *	One of the Leaf(s) in the Composite Structure.
	  *	Processes Float type elements
	  *
	  */
	class FloatElement: public InstructionElement
	{
        public:
            FloatElement(unsigned int size, char* name, std::string variable);
            FloatElement(unsigned int size, char* name);

            FloatElement(std::string size, std::string name, std::string variable);
            FloatElement(std::string size, std::string name); // new constructor
			~FloatElement();

			/**	Reads in data from the packet
			  *	The data must be the same size as a float or a double.
			  * If not it throws an error
			  */
            unsigned int Interpret(char* buffer);

			/** Displays data from packet in wireshark
			  * Used to Display data to the WireShark output
			  */
			char* Display();

		private:
	};
}


#endif //FLOAT_ELEMENT_H
