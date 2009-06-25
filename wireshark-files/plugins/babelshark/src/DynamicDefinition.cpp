// $Id$

#include "DynamicDefinition.h"

namespace BabelShark
{

   DynamicDefinition::DynamicDefinition(Instruction* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
      _Definitions[parameter] = type;
   }

   DynamicDefinition::~DynamicDefinition()
   {
   }

   Instruction* DynamicDefinition::Fetch(InstructionElement* parameter)
   {
       return NULL; //TODO
       //return _Definitions[parameter];
   }

   void DynamicDefinition::Add(Instruction* type, std::string parameter)
   {
      _Definitions[parameter] = type;
   }

}
