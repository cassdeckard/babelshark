// $Id$

#ifndef STATIC_DEFINITION_H
#define STATIC_DEFINITION_H

#include "TypeDefinition.h"

namespace BabelShark
{
    /** StaticDefinition is a simple subclass of TypeDefinition
      * that contains a static reference to an InstructionSet.
      */

    class StaticDefinition : public TypeDefinition
	{
        public:
           /** Constructor
             * Saves given InstructionNode as the definition of this type.
             */
           StaticDefinition(InstructionNode* type = NULL, std::string parameter = "");

           ~StaticDefinition();

           /** Fetch sets the supplied InstructionNode* to point to this type's
             * InstructionNode definition.
             *
             * @param target
             *   pointer to the Instruction* that should be set to the requested definition
             * @param parameter
             *   (unused)
             */
           void Fetch(InstructionNode** target, InstructionElement* parameter = NULL);

           void Define(InstructionNode* type);

		protected:


        private:
           /** _Definition
             * The InstructionNode that represents this type's definition.
             */
           InstructionNode* _Definition;
	};

}

#endif //STATIC_DEFINITION_H
