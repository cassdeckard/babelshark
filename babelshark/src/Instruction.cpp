#include "..\Instruction.h"


Instruction::Instruction()
{

}


//virtual function, base definition does nothing.
//should be implemented by any class inheriting from it.
void Instruction::Interpret(char* buffer)
{

}

//virtual function, base definition does nothing.
//will be used to Display data to the WireShark output
void Instruction::Display();

//virtual function, no implementation in base class
//used in the InstructionList class.
Instruction* Instruction::GetChild()
{

}

//virtual function, no implementation in base class
//used in the InstructionList class.
void Instruction::Add(Instruction*)
{

}

//virtual function, no implementation in base class
//used in the InstructionList class.
void Instruction::Remove(Instruction*)
{

}

//virtual function, no implementation in base class
//used in the InstructionList class.
void Instruction::CreateIterator()
{

}