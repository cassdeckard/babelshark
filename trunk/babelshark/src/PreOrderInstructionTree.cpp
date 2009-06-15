// $Id: PreOrderInstructionTree.cpp 37 2009-06-14 15:22:55Z thegordonemail $

#include "..\PreOrderInstructionTree.h"

namespace BabelShark
{
	PreOrderInstructionTree::PreOrderInstructionTree(Instruction* root) 
		: InstructionTree(root)
	{

	}

	PreOrderInstructionTree::~PreOrderInstructionTree(){
		return;
	}

	void PreOrderInstructionTree::First(){
		InstructionTree* i = _root->CreateIterator();

		if(i) {
			i->First();
			while(_iterators.size() > 0){
				_iterators.pop();
			}
			_iterators.push(i);
		}
		return;
	}

	Instruction* PreOrderInstructionTree::CurrentItem(){
		return _iterators.size() >0 ? _iterators.top()->CurrentItem() : 0;
	}

	void PreOrderInstructionTree::Next(){
		InstructionTree* i = _iterators.top()->CurrentItem()->CreateIterator();
		i->First();
		_iterators.push(i);

		while(_iterators.size() > 0 && _iterators.top()->IsDone()){
			//delete _iterators.pop();
			//TODO This is not working but should be.  Its returning a pointer
			_iterators.top()->Next();
		}
		return;
	}

	bool PreOrderInstructionTree::IsDone(){
		return _iterators.size() >0 ? false : true;
	}

}