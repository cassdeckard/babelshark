// $Id: Iterator.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "Iterator.h"

namespace BabelShark
{

	Iterator::Iterator(Instruction* root){
		_rootNode = root;
		return;
	}

	Iterator::~Iterator(){
		return;
	}


    void Iterator::First()
    {
    }

    Instruction* Iterator::CurrentItem()
    {
        return NULL;
    }

    void Iterator::Next()
    {
    }

    bool Iterator::IsDone()
    {
        return true;
    }

}
