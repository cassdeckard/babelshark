// $Id$

#ifndef TYPE_DEFINITION_H
#define TYPE_DEFINITION_H

#include "InstructionNode.h"
#include "Observer.h"

namespace BabelShark
{
    class InstructionElement; // forward declaration

    /** TypeDefinition is the abstract base class for user-defined types.
      */
	class TypeDefinition : public Observer
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
             *   pointer to the InstructionNode* that should be set to the requested definition
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

           /** Define is only used by static definitions. It is used to change
             * the definition
             *
             * @param type
             *   InstructionNode* that represents this static definition
             */
           virtual void Define(InstructionNode* type) { }

		protected:

        private:
	};

}

#endif //TYPE_DEFINITION_H
