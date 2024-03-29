// $Id$

#ifndef INSTRUCTION_ELEMENT_H
#define INSTRUCTION_ELEMENT_H

#ifndef MIN
#define MIN(a, b)  (((a) < (b)) ? (a) : (b))
#endif

#include <bitset>
#include <list>
//#include "Instruction.h"
#include "Subject.h"
#include "TypeDefinition.h"

/*
	Design Pattern Used: Composite
    Class: InstructionElement
	         The Leaf portion of the Composite pattern.
			 Handles processing at the lowest level.
*/



namespace BabelShark
{
    /** InstructionElement is another abstract class derived from Instruction.
      * In represents a primitive unit of packet data that Dissector will
      * interpret, and is a leaf in the Instruction tree.
      *
      * <b>Pattern roles:</b>
      *  - Composite::Leaf
      *  - Iterator::ConcreteAggregate
      *  - Interpreter::TerminalExpression
      *  - Observer::Subject
      *
      */
	class InstructionElement: public Instruction, public Subject
	{
		public:
            InstructionElement(std::string size, std::string name, std::string variable = "");
			~InstructionElement();

			//virtual function, base definition does nothing.
			//should be implemented by any class inheriting from it.
            virtual unsigned int Interpret(char* buffer);

			//virtual function, base definition does nothing.
			//will be used to Display data to the WireShark output
			virtual char* Display();

			//virtual function, no implementation in base class
			//used in the InstructionList class.
			Instruction* GetChild();

			//Creates a NullIterator because an InstructionElement
			//should have no children.
            Iterator*  CreateIterator();

            /** A utility function used to create a bitmask for subtypes
              * to use if they are looking at only a portion of a byte of
              * data.
              *
              * @param val
              *   number of bits to mask
              * @return
              *   bitmask to reveal <i>val</i> bytes
              */
            static unsigned long long SetupBitMask(unsigned int val);

            /** A utility function for subclasses whose size is
              * in bits to convert that to bytes to implement the
              * GetSizeInBytes() function.
              *
              * @param bits
              *   number of bits
              * @return
              *   rounded up number of bytes
              */
            unsigned int DetermineSizeInBytes(int bits);

            // override
            unsigned int NumSubtrees();

            /* PHASE 2 UPDATES */

            /** SimpleDisplay() returns a simplified representations of
              * the element's current interpreted value. Mainly for use
              * in variable references.
              */
            std::string SimpleDisplay();

        protected:
            /** Holds the result of the last call to Interpret()
              */
            std::string _InterpretedData;
	};
}

#endif //INSTRUCTION_ELEMENT_H
