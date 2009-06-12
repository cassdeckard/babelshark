#ifndef INSTRUCTION_H
#define INSTRUCTION_H
/*
	Class:Instruction
		used purely as a Composite portion of the Composite Design Pattern
		inherited by InstructionElement and InstructionSet
*/



namespace BabelShark
{
	class Instruction
	{
		Instruction();
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
		
		//virtual function, no implementation in base class
		//used in the InstructionList class.
		virtual void Add(Instruction*);
		
		//virtual function, no implementation in base class
		//used in the InstructionList class.
		virtual void Remove(Instruction*);
		
		//virtual function, no implementation in base class
		//used in the InstructionList class.
		virtual void CreateIterator();

		protected:
			//Iterator has not been implemented yet.  When it is
			//this is to be used to construct the different
			//Iterator objects in InstructionElement and InstructionSet classes
			//Iterator* _Iter;

		private:
	};


}

#endif //INSTRUCTION_H