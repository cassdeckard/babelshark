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

			//TODO -- Implement this
			//Will be used to read in data from packet (I think??)
			void Interpret(char* buffer);

			//TODO -- Implement this
			//will be used to Display data to the WireShark output
			char* Display();
		private:
			std::string _InterpretedData;
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
			//NullIterator* nullIterator;
	};
}


#endif //ASCII_ELEMENT_H