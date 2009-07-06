// $Id$

#ifndef DYNAMIC_DEFINITION_H
#define DYNAMIC_DEFINITION_H

#include "TypeDefinition.h"
#include "InstructionElement.h"
#include <map>

namespace BabelShark
{
    /** DynamicDefinition is a subclass of TypeDefinition
      * that contains a dynamic reference to a mapping of InstructionSets.
      *
      * <b>Pattern roles:</b>
      *  - Observer::Observer
      */
    class DynamicDefinition : public TypeDefinition
	{
        public:

           /** Constructor
             */
           DynamicDefinition(InstructionNode* type = NULL, std::string parameter = "");

           ~DynamicDefinition();

           /** Fetch sets the supplied InstructionNode* to point to this type's
             * InstructionNode definition.
             *
             * @param target
             *   pointer to the Instruction* that should be set to the requested definition
             * @param parameter
             *   InstructionElement whose value the Instruction is dependent upon
             */
           void Fetch(InstructionNode** target, InstructionElement* parameter);

           /** Add adds a value-type pair to the definition.
             *
             * @param type
             *   type half of the value-type pair
             * @param value
             *   value half ot the value-type pair
             */
           void Add(TypeDefinition* typeDef, std::string parameter);

           /** Update is called by an observed InstructionElement when its
             * state changes, to notify that it needs to update the
             * Instruction's dependent upon that parameter.
             *
             * <b>Pattern roles:</b>
             *  - Proxy::Observer::Update()
             *
             * @param subject
             *   pointer to observed element that has changed
             */
           void Update(Subject* subject);

		protected:


        private:

           /** _Definitions
             * Mapping of values to types.
             */
           std::map<std::string, TypeDefinition*>           _Definitions;

           /** _Subjects
             * Mapping of watched variables to the type associated with their
             * current value.
             */
           std::map<InstructionElement*, InstructionNode**> _Subjects;
	};

}

#endif //DYNAMIC_DEFINITION_H
