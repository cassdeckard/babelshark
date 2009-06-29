// $Id$

#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include "InstructionNode.h"

namespace BabelShark
{
    class InstructionElement; // forward declaration

    /** TypeDefinition is the abstract base class for user-defined types.
      */
	class TypeDefinition
	{
        public:

           /** Constructor
             */
           TypeDefinition(InstructionNode* type = NULL, std::string parameter = "")
           {
           }

           ~TypeDefinition()
           {
           }

           /** Fetch sets the supplied InstructionNode* to point to this type's
             * InstructionNode definition.
             *
             * @param target
             *   pointer to the Instruction* that should be set to the requested definition
             * @param parameter
             *   (for DynamicDefinition)
             */
           virtual void Fetch(InstructionNode** target, InstructionElement* parameter = NULL) { }

           /** Add is used by DynamicDefinition to add a value-type pair to the definition.
             *
             * @param type
             *   type half of the value-type pair
             * @param value
             *   value half ot the value-type pair
             */
           virtual void Add(TypeDefinition* type, std::string value) { }

           /** Update is used by DynamicDefinition. It is called by an observed
             * InstructionElement when its state changes, to notify that it needs
             * to update the Instructions dependent upon that parameter.
             *
             * @param subject
             *   pointer to observed element that has changed
             */
           virtual void Update(InstructionElement* subject) { }

           virtual void Define(InstructionNode* type) { }

		protected:

        private:
	};

}

#endif //TYPE_DEFINITION_H
