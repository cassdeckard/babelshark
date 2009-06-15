// $Id$

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <string>
/*
	Design Pattern Used: Composite
	Class:Instruction
		used purely as a Composite portion of the Composite Design Pattern
		inherited by InstructionElement and InstructionSet
		Composite allows objects to be treated uniformly.
*/



namespace BabelShark
{
	class Instruction
	{
		public:
			Instruction(unsigned int size, char* name);
			virtual ~Instruction();

			//virtual function, base definition does nothing.
			//should be implemented by any class inheriting from it.
			virtual void Interpret(char* buffer);

			//virtual function, base definition does nothing.
			//will be used to Display data to the WireShark output
			virtual char* Display();

			//virtual function, no implementation in base class
			//used in the InstructionList class.
			virtual Instruction* GetChild();

			//virtual function, implementation does nothing.
			//used in the InstructionList class.
			virtual void Add(Instruction*);

			//virtual function, no implementation in base class
			//used in the InstructionList class.
			virtual void Remove(Instruction*);

			//virtual function, no implementation in base class
			//used in the InstructionList class.
			virtual void CreateIterator();

			void SetSize(unsigned int size){ _Size = size;}
			void SetName(char* name){ _Name = name;}

			unsigned int GetSize() { return _Size;}
			char* GetName(){ return (char*)(_Name.c_str());}
			unsigned int GetSizeInBytes(){return _SizeInBytes;}

		protected:
			unsigned int _Size;
			unsigned int _SizeInBytes;
			std::string _Name;
			//Iterator has not been implemented yet.  When it is
			//this is to be used to construct the different
			//Iterator objects in InstructionElement and InstructionSet classes
			//Iterator* _Iter;

		private:
	};


}

#endif //INSTRUCTION_H