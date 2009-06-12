#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include "Instruction.h"


namespace BabelShark
{
	class InstructionSet: public Instruction
	{
		public:
			//returns the first Child of the InstructionSet list.
			Instruction* GetChild();
			//Adds a child Instruction to the list.
			void Add(Instruction*);
			//Removes a child Instruction from the list.
			void Remove(Instruction*);
			//attempts to Interpret the buffer according to the children.
			void Interpret(char* buffer);
			//Creates an iterator used to traverse the direct children.
			void CreateIterator();
		private:
			IteratorList* Iterator;
	}
}

#endif//INSTRUCTION_SET_H