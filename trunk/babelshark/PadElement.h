// $Id$

#ifndef PAD_ELEMENT_H
#define PAD_ELEMENT_H

#include "InstructionElement.h"

namespace BabelShark
{
	class PadElement: public InstructionElement
	{
		public:
			PadElement(unsigned int size, char* name);
			~PadElement();

			//TODO -- Implement this
			//Will be used to read in data from packet (I think??)
			void Interpret(char* buffer);

			//TODO -- Implement this
			//will be used to Display data to the WireShark output
			char* Display();
		private:
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
			//NullIterator* nullIterator;
	};
}


#endif //PAD_ELEMENT_H