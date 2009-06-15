// $Id$

#ifndef INSTRUCTION_ELEMENT_H
#define INSTRUCTION_ELEMENT_H

#define BIT_MASK_MAX_SIZE 64

#include <bitset>
#include "Instruction.h"

namespace BabelShark
{
	class InstructionElement: public Instruction
	{
		public:
			InstructionElement(unsigned int size, char* name);
			~InstructionElement();

			//virtual function, base definition does nothing.
			//should be implemented by any class inheriting from it.
			virtual void Interpret(char* buffer);

			//virtual function, base definition does nothing.
			//will be used to Display data to the WireShark output
			virtual char* Display();

			//virtual function, no implementation in base class
			//used in the InstructionList class.
			Instruction* GetChild();

			//Creates a NullIterator because an InstructionElement
			//should have no children.
            void CreateIterator();

            // takes an Input Size and forms a bitmask based on it.
            static std::bitset<BIT_MASK_MAX_SIZE> SetupBitMask(unsigned int val);

            // rounds up bit size to byte size
            unsigned int DetermineSizeInBytes(int bits);

        protected:
            std::string _InterpretedData;

		private:
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
            //NullIterator* nullIterator;

	};
}

#endif //INSTRUCTION_ELEMENT_H