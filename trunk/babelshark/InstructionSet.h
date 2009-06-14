// $Id$

#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include "Instruction.h"

#include <vector>

namespace BabelShark
{
	typedef std::vector<Instruction*> InstructionCollection;
	class InstructionSet: public Instruction
	{
		public:
			InstructionSet(unsigned int size, char* name);
			~InstructionSet();

			//returns the first Child of the InstructionSet list.
			Instruction* GetChild();

			//Adds a child Instruction to the list.
			void Add(Instruction*);

			//attempts to Interpret the buffer according to the children.
			void Interpret(char* buffer);

            //will be used to Display data to the WireShark output
            char* Display();

			//Creates an iterator used to traverse the direct children.
			void CreateIterator();
			InstructionCollection::iterator GetIterator(){ return _ListIter;}

            // Override
            unsigned int GetSizeInBytes();
		private:
			InstructionCollection _List;
			InstructionCollection::iterator _ListIter;
	};
}

#endif//INSTRUCTION_SET_H