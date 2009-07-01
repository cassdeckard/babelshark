// $Id$

#include "Instruction.h"
#include "NullIterator.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    // OLD AND BUSTED
	Instruction::Instruction(unsigned int size, char* name)
		:_Size(size),
		 _Name(name)
	{
	}

    // NEW HOTNESS
    Instruction::Instruction(std::string size, std::string name)
        :_Name(name.c_str()),
         _Size(1)
    {
    	if ( ! SetSize(size) )
    	{
    		// add us to DD's initialize list
    		DataDictionary::Instance()->ToInitialize(this);
    	}
    }

	Instruction::~Instruction()
	{

	}
	//virtual function, base definition does nothing.
	//should be implemented by any class inheriting from it.
	unsigned int Instruction::Interpret(char* buffer)
	{
        return 0;
	}

	//virtual function, base definition does nothing.
	//will be used to Display data to the WireShark output
	char* Instruction::Display()
	{
		return 0;
	}

	//virtual function, no implementation in base class
	//used in the InstructionList class.
	Instruction* Instruction::GetChild()
	{
		return 0;
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
	Iterator* Instruction::CreateIterator()
	{
		return new NullIterator(this);
	}

    //virtual function, overridden by InstructionElement
    // For keeping track of subtrees
    unsigned int Instruction::NumSubtrees()
    {
        unsigned int result = 0; // don't count this! It might not be a subtree

        // for all my children
        for (Iterator* it = this->CreateIterator(); ! it->IsDone(); it->Next())
        {
            result += it->CurrentItem()->NumSubtrees();
        }

        return result;
    }

    void Instruction::Initialize()
    {
    	// If size was given as a string, it should be a variable. Look it up,
    	// and attach to it.
    	if (_SizeString.compare("") != 0)
    	{
    		_SizeParam = DataDictionary::Instance()->LookupVariable(_SizeString);
    		_SizeParam->Attach(this);
    	}
    }

    void Instruction::Update(Subject* subject)
    {
    	if (subject == _SizeParam)
    	{
    		SetSize(_SizeParam->SimpleDisplay());
    	}
    }


	bool Instruction::SetSize(std::string size)
	{
        std::istringstream myStream(size);
        unsigned int intSize;

        if (myStream >> intSize)
        {
    		printf("Instruction '%s' setting size to '%u'.\n", _Name.c_str(), intSize);
            _Size = intSize;
            _SizeString = "";
            return true;
        }

		// Size not in integer format - must be a variable
		printf("Instruction '%s' given string '%s' as size.\n", _Name.c_str(), size.c_str());
		_SizeString = size;
		return false;
	}
}
