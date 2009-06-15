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
		/*InstructionCollection::iterator i = _root->GetIterator();

		if(i) {
			i->First();
			_iterators.RemoveAll();
			_iterators.Push(i);
		}*/
		return;
	}

	Instruction* PreOrderInstructionTree::CurrentItem(){
		//return _iterators.Size() >0 ? _iterators.Top()->CurrentItem() : 0;
		return 0;
	}

	void PreOrderInstructionTree::Next(){
		/*InstructionCollection::iterator i = _iterators.Top()->CurrentItem()->CreateIterator();
		i->First();
		_iterators.Push(i);

		while(_iterators.Size() > 0 && _iterators.Top()->IsDone()){
			delete _iterators.Pop();
			_iterators.Top()->Next();
		}*/
		return;
	}

	bool PreOrderInstructionTree::IsDone(){
		//TODO
		return false;
	}

}