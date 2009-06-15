// $Id$

#ifndef PAD_ELEMENT_H
#define PAD_ELEMENT_H

#include "InstructionElement.h"

/*
	Design Pattern Used: Composite
	Class: PadElement
	Parent: InstructionElement
	One of the Leaf(s) in the Composite Structure.
	Processes Pad type elements
*/


namespace BabelShark
{
	class PadElement: public InstructionElement
	{
		public:
			PadElement(unsigned int size, char* name);
			~PadElement();
			
			//used to read in data from packet
			void Interpret(char* buffer);

			//used to Display data to the WireShark output
			char* Display();
		private:
	};
}


#endif //PAD_ELEMENT_H