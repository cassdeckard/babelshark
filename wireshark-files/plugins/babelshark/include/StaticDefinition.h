// $Id$

#ifndef STATIC_DEFINITION_H
#define STATIC_DEFINITION_H

#include "TypeDefinition.h"
#include "Instruction.h"
#include "InstructionElement.h"

namespace BabelShark
{
    class StaticDefinition : public TypeDefinition
	{
        public:

           StaticDefinition(Instruction* type, std::string parameter);

           ~StaticDefinition();

           Instruction* Fetch(InstructionElement* parameter);

           void Add(Instruction* type, std::string parameter);

		protected:


        private:
           Instruction* _Definition;
	};

}

#endif //STATIC_DEFINITION_H
