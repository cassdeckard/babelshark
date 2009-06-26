// $Id$

#include "StaticDefinition.h"

namespace BabelShark
{

   StaticDefinition::StaticDefinition(InstructionNode* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
      _Definition = type;
   }

   StaticDefinition::~StaticDefinition()
   {
   }

   void StaticDefinition::Fetch(InstructionNode** target, InstructionElement* parameter)
   {
       target = &_Definition;
   }

   void StaticDefinition::Add(InstructionNode* type, std::string parameter)
   {
       // THIS SHOULD NEVER BE CALLED
   }

}
