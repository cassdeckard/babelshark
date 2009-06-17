// $Id$

#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include "Instruction.h"
#include "ListIterator.h"

#include <vector>


namespace BabelShark
{
	/**
		Class: InstructionSet
		Design Pattern Used: Composite
			The Composite portion of the Composite pattern.
			This contains Instruction* children.
	*/
	class InstructionSet: public Instruction
	{
		public:
			/** Constructor*/
			InstructionSet(unsigned int size, char* name);

			/** Destructor*/
			~InstructionSet();

			/**returns the first Child of the InstructionSet list regardless of number of children present.*/
			Instruction* GetChild();

			/**Adds a child Instruction to the list.*/
			void Add(Instruction*);

			/**attempts to Interpret the buffer according to the children.*/
			void Interpret(char* buffer);

            /**will be used to Display data to the WireShark output*/
            char* Display();

			/**Creates an iterator used to traverse the direct children.*/
			Iterator* CreateIterator();
			InstructionCollection::iterator GetIterator(){ return _ListIter;}

            /** Returns the sum of calling GetSizeInBytes on all children
            Override the function defined in instruction*/
            unsigned int GetSizeInBytes();

            /** Returns the sum of calling NumSubTrees on all children
            Override the [dummy] function defined in instruction*/
            unsigned int NumSubtrees();
		private:
			/** Used to store the direct children*/
			InstructionCollection _List;
			/**Creates an stl::iterator used to traverse the direct children.*/
			InstructionCollection::iterator _ListIter;
	};
}

#endif//INSTRUCTION_SET_H