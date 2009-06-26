// $Id$

#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include "InstructionNode.h"

namespace BabelShark
{
    class InstructionElement; // forward declaration
	class TypeDefinition
	{
        public:

           TypeDefinition(InstructionNode* type, std::string parameter)
           {
           }

           ~TypeDefinition()
           {
           }

           virtual void Fetch(InstructionNode** target, InstructionElement* parameter) { }

           virtual void Add(InstructionNode* type, std::string parameter) { }

           virtual void Update(InstructionElement* subject) { }

		protected:


        private:
	};

}

#endif //TYPE_DEFINITION_H
