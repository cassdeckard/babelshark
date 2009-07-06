// $Id: ListIterator.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "ListIterator.h"

namespace BabelShark
{
	/*ListIterator fills in the role in Iterator pattern as well as filling the adapter pattern
	adapting the stl:Iterator to the Iterator pattern*/
	ListIterator::ListIterator(Instruction* root, InstructionCollection list)
		: Iterator(root)
	{
		_List = list;
		_ListIter = _List.begin();
	}

	void ListIterator::First()
	{
		_ListIter = _List.begin();
	}

	Instruction* ListIterator::CurrentItem()
	{
		return *_ListIter;
	}

	void ListIterator::Next()
	{
		_ListIter++;
	}

	bool ListIterator::IsDone()
	{
		if(_ListIter == _List.end()){
			return true;
		}
		return false;
	}


	ListIterator::~ListIterator(){
		return;
	}

}