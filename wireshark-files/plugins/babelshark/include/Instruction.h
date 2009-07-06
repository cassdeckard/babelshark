// $Id$

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
#include <vector>
#include "Iterator.h"
#include "Observer.h"

namespace BabelShark
{
    class Iterator;            // forward declaration
    class InstructionElement;  // forward declaration

    /** Instruction is the base abstract class for all instructions.
      * It declares all the virtual functions which will be implemented by
      * all of the Instruction subclasses. An Instruction represents some
      * unit of packet data that Dissector will interpret. This could be
      * either a primitive type (such as a string or an integer) or an
      * aggregate type containing a set of other types.
      *
      * A tree of Instructions is created by the PDI Parser based on the
      * definition supplied by the user. Dissector uses an Instruction
      * by calling Interpret() to pass it the part of the packet data buffer
      * it is responsible for, then calling Display() to retrieve the
      * interpreted data to be displayed to the user.
      *
      * <b>Pattern roles:</b>
      *  - Composite::Component
      *  - Iterator::Aggregate
      *  - Interpreter::AbstractExpression
      */
	class Instruction : public Observer
	{
		public:
            Instruction(std::string size, std::string name);
			virtual ~Instruction();

            /** Interprets incoming packet data.
              * Reads data from buffer and stores interpretation
              * to later be displayed.
              *
              * <b>Pattern roles:</b>
              *  - Interpreter::Interpret
              *
              * @param buffer the packet data to interpret
              * @return number of bits used in last byte
              */
			virtual unsigned int Interpret(char* buffer);

            /** Displays interpreted packet data.
              *
              * <b>Pattern roles:</b>
              *  - Composite::Operation
              */
			virtual char* Display();


            /** Returns first child of this Instruction.
              *
              * <b>Pattern roles:</b>
              *  - Composite::GetChild
              */
			virtual Instruction* GetChild();

            /** Adds child to this Instruction.
              *
              * <b>Pattern roles:</b>
              *  - Composite::Add
              *
              * @param instruction the Instruction to add
              */
			virtual void Add(Instruction*);

            /** Removes child from this Instruction.
              *
              * <b>Pattern roles:</b>
              *  - Composite::Remove
              *
              * @param instruction the Instruction to remove
              */
			virtual void Remove(Instruction*);

            /** Creates and returns an iterator for this Instruction's
              * children.
              *
              * <b>Pattern roles:</b>
              *  - Iterator::CreateIterator
              *
              * @return an Iterator pointing to this Instruction's first child
              */
            virtual Iterator* CreateIterator();

            /** Returns the number of bytes this Instruction interprets,
              * rounded up.
              *
              * @return size in bytes
              */
            virtual unsigned int GetSizeInBytes(){return _SizeInBytes; }

            /** Performs initialization that depends on all Instruction
              * objects being instantiated.
              *
              */
            virtual void Initialize();

			void SetSize(unsigned int size){ _Size = size;}
			bool SetSize(std::string size);
			void SetName(std::string name){ _Name = name;}

			unsigned int GetSize() { return _Size;}
			char* GetName(){ return (char*)(_Name.c_str());}

            /** Returns the total amount of subtree nodes that occur
              * beneath this node. Will be used by Dissector to allocate
              * memory for keeping the expanded state (ett) of subtrees.
              *
              * @return
              *   rounded up number of subtrees below this node
              */
            virtual unsigned int NumSubtrees();

            // overriding Observer::Update()
            void Update(Subject* subject);

		protected:
			unsigned int        _Size;
			unsigned int        _SizeInBytes;
			InstructionElement* _SizeParam;
			std::string         _Name;
			std::string         _SizeString;

		private:
	};

}

#endif //INSTRUCTION_H
