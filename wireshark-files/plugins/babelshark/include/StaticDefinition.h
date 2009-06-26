// $Id$

#ifndef STATIC_DEFINITION_H
#define STATIC_DEFINITION_H

#include "TypeDefinition.h"

namespace BabelShark
{
    class StaticDefinition : public TypeDefinition
	{
        public:

           StaticDefinition(InstructionNode* type, std::string parameter);

           ~StaticDefinition();

           void Fetch(InstructionNode** target, InstructionElement* parameter);

           void Add(InstructionNode* type, std::string parameter);

		protected:


        private:
           InstructionNode* _Definition;
	};

}

#endif //STATIC_DEFINITION_H
