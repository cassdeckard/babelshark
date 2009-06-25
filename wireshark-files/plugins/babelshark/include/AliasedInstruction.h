// $Id$

#ifndef ALIASED_INSTRUCTION_H
#define ALIASED_INSTRUCTION_H
#include "InstructionNode.h"
#include "ListIterator.h"

#include <vector>

namespace BabelShark
{
	/**
		Class: AliasedInstruction
		Design Pattern Used: Composite
			The Composite portion of the Composite pattern.
			This contains Instruction* children.
	*/
	class AliasedInstruction: public InstructionNode
	{
		public:
			/** Constructor
				Just calls parent constructor, nothing specific to this class
			*/
            AliasedInstruction(unsigned int size, char* name)
                : InstructionNode(size, name)
            {
            }

            AliasedInstruction(unsigned int size, char* name, Instruction* alias)
                : InstructionNode(size, name),
                  _RealSubject(alias)
            {
            }

			/** Destructor
				Empty desctructor class
			*/
            ~AliasedInstruction()
            {
            }

			/** GetChild
				Returns the first Child of the AliasedInstruction list regardless of number of children present.
				This was mainly for testing for the presence of children but is no longer used
				May be taken out at some point in the future

				Does not match the standard pattern definition since we're using an iterator instead
			*/
            Instruction* GetChild() { return _RealSubject->GetChild(); }

			/**	Add
				Adds a child Instruction to the list.
				Standard add of the composite pattern
				*/
            void Add(Instruction* instruction) { _RealSubject->Add(instruction); }

			/** Interpret
				Currently an empty function since the dissector will just look directly at the children
				*/
            void Interpret(char* buffer) {  _RealSubject->Interpret(buffer); }

            /** Display
            	For the instruction set this just prints out the name of the set
            	the printing out of the names/content of the children will be handled by the dissector calling
            	the display function one at a time for each child
            */
            char* Display() { return _RealSubject->Display(); }

			/** CreateIterator
				This is taking the part of the ConcreteList in the iterator pattern
				Although we haven't done append/remove we don't need to since our list is static when we are iterating
				over it
			*/
			Iterator* CreateIterator() { return _RealSubject->CreateIterator(); }

            /** GetSizeInBytes
            	Returns the sum of calling GetSizeInBytes on all children
            	Override the function defined in instruction
            	*/
            unsigned int GetSizeInBytes() { return _Size * _RealSubject->NumSubtrees(); }

            /** NumSubTrees
            	Returns the sum of calling NumSubTrees on all children
            	Override the [dummy] function defined in instruction
            	*/
            unsigned int NumSubtrees() { return _RealSubject->NumSubtrees(); }

		private:
			/** The root of the Instruction tree this object will be a placeholder for
              */
			Instruction* _RealSubject;
	};
}

#endif //ALIASED_INSTRUCTION_H