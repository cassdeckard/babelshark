#include "..\AsciiElement.h"

/*
//Chris's note - Dan had this out there, but I suspect the easiest element to implement will be
//an unsigned int so it might be best to start with that one first.  After we get that working we
//can probably just mimic the same approach in the sibling classes

//Note I have **NOT** compiled this.  Just typeing and hoping I don't make mistakes at this point
*/;
namespace BabelShark
{


	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void Interpret(char* buffer)
	{
		//Implement me!
	}

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	void Display()
	{
		//Implement me!
	}

	//Since this is a leaf node it won't have a child
	Instruction* GetChild()
	{
		return 0;
	}

	//Since this is a leaf node it won't have a child
	void Add(Instruction*)
	{
		return;
	}

	//Since this is a leaf node it won't have a child
	void Remove(Instruction*)
	{
		return;
	}

	//TODO
	//I don't understand why this is returning a null iterator, but parent class did. :)
	//creates a NULL iterator from the object defined in Instruction
	void CreateIterator()
	{
		//_Iter = new NullIterator();
		return;
	}
}
}