// $Id: NullIterator.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "..\NullIterator.h"

namespace BabelShark
{
	NullIterator::NullIterator(Instruction* root)
		: Iterator(root)
	{

	}


	NullIterator::~NullIterator(){
		return;
	}

}