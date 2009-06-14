// $Id$

#ifndef ASCII_ELEMENT_H
#define ASCII_ELEMENT_H

#include "InstructionElement.h"

namespace BabelShark
{
	class AsciiElement: public InstructionElement
	{
		public:
			AsciiElement(unsigned int size, char* name);
			~AsciiElement();

			//Will be used to read in data from packet (I think??)
			void Interpret(char* buffer);

			//will be used to Display data to the WireShark output
			char* Display();
		private:
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
			//NullIterator* nullIterator;


            // TODO: DESCRIPTION
            std::string AsciiElement::Printable(char inChar);
	};
}


#endif //ASCII_ELEMENT_H