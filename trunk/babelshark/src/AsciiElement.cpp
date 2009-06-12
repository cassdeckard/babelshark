#include "..\AsciiElement.h"

namespace BabelShark
{
//Chris's note - Dan had this out there, but I suspect the easiest element to implement will be
//an unsigned int so it might be best to start with that one first.  After we get that working we
//can probably just mimic the same approach in the sibling classes

//If anyone can figure out why the semicolon up on line 2 is required it would be much appreciated


	//TODO -- Implement this
	//Will be used to read in data from packet (I think??)
	void AsciiElement::Interpret(char* buffer)
	{
		//Implement me!
	}

	//TODO -- Implement this
	//will be used to Display data to the WireShark output
	char* AsciiElement::Display()
	{
		//Implement me!
		return 0;
	}


/*  Commenting out the three functions below since we should be able to let it default to the 
*   parent object
	//Since this is a leaf node it won't have a child
	Instruction* AsciiElement::GetChild()
	{
		return 0;
	}

	//Since this is a leaf node it won't have a child
	void AsciiElement::Add(Instruction*)
	{
		return;
	}

	//Since this is a leaf node it won't have a child
	void AsciiElement::Remove(Instruction*)
	{
		return;
	}
*/
	//TODO
	//I don't understand why this is returning a null iterator, but parent class did. :)
	//creates a NULL iterator from the object defined in Instruction
	void AsciiElement::CreateIterator()
	{
		//_Iter = new NullIterator();
		return;
	}
	
}