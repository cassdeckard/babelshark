#ifndef INSTRUCTION_ELEMENT_H
#define INSTRUCTION_ELEMENT_H
#include "Instruction.h"

namespace BabelShark
{
	class InstructionElement: public Instruction
	{
		public:
			InstructionElement();
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

			//Recall we are using the composite pattern
			//Since this is the parent class for all leaf nodes it won't have the ability to add children
			void InstructionElement::Add(Instruction*);

			//Recall we are using the composite pattern
			//Since this is the parent class for all leaf nodes it won't have the ability to remove children
			void InstructionElement::Remove(Instruction*);

			//Creates a NullIterator because an InstructionElement
			//should have no children.
			void CreateIterator();
		private:
			unsigned int _Size;
			//NullIterator has not been implented yet.
			//when it is, this class is to construct an object
			//of type NullIterator
			//NullIterator* nullIterator;
	};
}

#endif //INSTRUCTION_ELEMENT_H