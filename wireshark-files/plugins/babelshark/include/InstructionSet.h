// $Id$

#ifndef INSTRUCTION_SET_H
#define INSTRUCTION_SET_H
#include "InstructionNode.h"
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
	class InstructionSet: public InstructionNode
	{
		public:
			/** Constructor
				Just calls parent constructor, nothing specific to this class
			*/
			InstructionSet(unsigned int size, char* name);

			/** Destructor
				Empty desctructor class
			*/
			~InstructionSet();

			/** GetChild
				Returns the first Child of the InstructionSet list regardless of number of children present.
				This was mainly for testing for the presence of children but is no longer used
				May be taken out at some point in the future

				Does not match the standard pattern definition since we're using an iterator instead
			*/
			Instruction* GetChild();

			/**	Add
				Adds a child Instruction to the list.
				Standard add of the composite pattern
				*/
			void Add(Instruction*);

			/** Interpret
				Currently an empty function since the dissector will just look directly at the children
				*/
            unsigned int Interpret(char* buffer);

            /** Display
            	For the instruction set this just prints out the name of the set
            	the printing out of the names/content of the children will be handled by the dissector calling
            	the display function one at a time for each child
            */
            char* Display();

			/** CreateIterator
				This is taking the part of the ConcreteList in the iterator pattern
				Although we haven't done append/remove we don't need to since our list is static when we are iterating
				over it
			*/
			Iterator* CreateIterator();

            /** GetSizeInBytes
            	Returns the sum of calling GetSizeInBytes on all children
            	Override the function defined in instruction
            	*/
            unsigned int GetSizeInBytes();

            /** NumSubTrees
            	Returns the sum of calling NumSubTrees on all children
            	Override the [dummy] function defined in instruction
            	*/
            unsigned int NumSubtrees();

		private:
			/** Used to store the direct children*/
			InstructionCollection _List;
			/**Creates an stl::iterator used to traverse the direct children.*/
			InstructionCollection::iterator _ListIter;
	};
}

#endif//INSTRUCTION_SET_H