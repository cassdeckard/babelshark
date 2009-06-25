// $Id$

#ifndef DYNAMIC_DEFINITION_H
#define DYNAMIC_DEFINITION_H

#include "TypeDefinition.h"
#include "Instruction.h"
#include "InstructionElement.h"
#include <map>

namespace BabelShark
{
    class DynamicDefinition : public TypeDefinition
	{
        public:

           DynamicDefinition(Instruction* type, std::string parameter);

           ~DynamicDefinition();

           Instruction* Fetch(InstructionElement* parameter);

           void Add(Instruction* type, std::string parameter);

		protected:


        private:
           std::map<std::string, Instruction*>         _Definitions;
           std::map<InstructionElement*, Instruction*> _Subjects;
	};

}

#endif //DYNAMIC_DEFINITION_H
