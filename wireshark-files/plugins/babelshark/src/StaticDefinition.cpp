// $Id$

#include "StaticDefinition.h"

namespace BabelShark
{

   StaticDefinition::StaticDefinition(Instruction* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
      _Definition = type;
   }

   StaticDefinition::~StaticDefinition()
   {
   }

   Instruction* StaticDefinition::Fetch(InstructionElement* parameter)
   {
       return _Definition;
   }

   void StaticDefinition::Add(Instruction* type, std::string parameter)
   {
       // THIS SHOULD NEVER BE CALLED
   }

}
