#include "Instruction.h"

namespace BabelShark
{
	class InstructionElement
	{
		public:
			InstructionElement();
			~InstructionElement();
			
			//virtual function, base definition does nothing.
			//should be implemented by any class inheriting from it.
			void Interpret(char* buffer);
			
			//virtual function, base definition does nothing.
			//will be used to Display data to the WireShark output
			char* Display();
			
			//virtual function, no implementation in base class
			//used in the InstructionList class.
			Instruction* GetChild();
			
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

