// $Id$

#ifndef ITERATOR_H
#define ITERATOR_H

#include "Instruction.h"

namespace BabelShark
{
    class Instruction; // forward declaration
	class Iterator
	{
		public:
			Iterator(Instruction* root);

			~Iterator();

			virtual void First();

            virtual Instruction* CurrentItem();

            virtual void Next();

            virtual bool IsDone();

		protected:
			Instruction* _rootNode;
		private:
	};
}

#endif