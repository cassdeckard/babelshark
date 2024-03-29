// $Id $

#ifndef INSTRUCTION_NODE_H
#define INSTRUCTION_NODE_H
#include "Instruction.h"
#include "NullIterator.h"

#include <vector>

namespace BabelShark
{
    /**
        Class: InstructionNode
        Design Pattern Used: Composite
            The Composite portion of the Composite pattern.
            This is an abstract class that every composite Instruction type will inherit from.
    */
    class InstructionNode: public Instruction
    {
        public:
            /** Constructor
                Just calls parent constructor, nothing specific to this class
            */
            InstructionNode(std::string size, std::string name) // new constructor
                :Instruction(size, name)
            {

            }

            /** Destructor
                Empty desctructor class
            */
            ~InstructionNode()
            {
            }

            /** GetChild
                Returns the first Child of the InstructionNode list regardless of number of children present.
                This was mainly for testing for the presence of children but is no longer used
                May be taken out at some point in the future

                Does not match the standard pattern definition since we're using an iterator instead
            */
            virtual Instruction* GetChild() = 0;

            /** Add
                Adds a child Instruction to the list.
                Standard add of the composite pattern
                */
            virtual void Add(Instruction*) = 0;

            /** Interpret
                Currently an empty function since the dissector will just look directly at the children
                */
            virtual unsigned int Interpret(char* buffer) = 0;

            /** Display
                For the instruction set this just prints out the name of the set
                the printing out of the names/content of the children will be handled by the dissector calling
                the display function one at a time for each child
            */
            virtual char* Display() = 0;

            /** CreateIterator
                This is taking the part of the ConcreteList in the iterator pattern
                Although we haven't done append/remove we don't need to since our list is static when we are iterating
                over it
            */
            virtual Iterator* CreateIterator() = 0;

            /** GetSizeInBytes
                Returns the sum of calling GetSizeInBytes on all children
                Override the function defined in instruction
                */
            virtual unsigned int GetSizeInBytes() = 0;

            /** NumSubTrees
                Returns the sum of calling NumSubTrees on all children
                Override the [dummy] function defined in instruction
                */
            virtual unsigned int NumSubtrees() = 0;

        private:
    };
}

#endif //INSTRUCTION_NODE_H
