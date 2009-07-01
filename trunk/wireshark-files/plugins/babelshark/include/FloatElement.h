// $Id$

#ifndef FLOAT_ELEMENT_H
#define FLOAT_ELEMENT_H

#include <bitset>
#include "InstructionElement.h"

#define BIT_MASK_MAX_SIZE 64



namespace BabelShark
{
	/**
		\class FloatElement
		Design Pattern Used: Composite
		Parent: InstructionElement
		One of the Leaf(s) in the Composite Structure.
		Processes Float type elements

		**Notes: not completed in Phase I!**
	*/
	class FloatElement: public InstructionElement
	{
		public:
            FloatElement(unsigned int size, char* name);
            FloatElement(std::string size, std::string name); // new constructor
			~FloatElement();

			/**	TODO -- Implement this
				Will be used to read in data from packet
				*/
            unsigned int Interpret(char* buffer);

			/**TODO -- Implement this
			 Will be used to Display data to the WireShark output
			 */
			char* Display();

		private:
	};
}


#endif //FLOAT_ELEMENT_H