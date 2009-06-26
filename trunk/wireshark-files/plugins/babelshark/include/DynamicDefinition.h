// $Id$

#ifndef DYNAMIC_DEFINITION_H
#define DYNAMIC_DEFINITION_H

#include "TypeDefinition.h"
#include "InstructionElement.h"
#include <map>

namespace BabelShark
{
    class DynamicDefinition : public TypeDefinition
	{
        public:

           DynamicDefinition(InstructionNode* type, std::string parameter);

           ~DynamicDefinition();

           void Fetch(InstructionNode** target, InstructionElement* parameter);

           void Add(InstructionNode* type, std::string parameter);

           void Update(InstructionElement* subject);

		protected:


        private:
           std::map<std::string, InstructionNode*>          _Definitions;
           std::map<InstructionElement*, InstructionNode**> _Subjects;
	};

}

#endif //DYNAMIC_DEFINITION_H
