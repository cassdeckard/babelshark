// $Id$

#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include "Instruction.h"
#include "InstructionElement.h"

namespace BabelShark
{
	class TypeDefinition
	{
        public:

           TypeDefinition(Instruction* type, std::string parameter)
           {
           }

           ~TypeDefinition()
           {
           }

           virtual Instruction* Fetch(InstructionElement* parameter) { return NULL; }

           virtual void Add(Instruction* type, std::string parameter) { }

		protected:


        private:
	};

}

#endif //TYPE_DEFINITION_H
