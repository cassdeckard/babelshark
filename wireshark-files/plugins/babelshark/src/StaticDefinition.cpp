// $Id$

#include "StaticDefinition.h"
#include <sstream>

namespace BabelShark
{

   StaticDefinition::StaticDefinition(InstructionNode* type, std::string parameter)
//      : TypeDefinition(type, parameter)
   {
      std::stringstream ss;
      ss << "StaticDefinition( {" << type << "}, " << parameter.c_str() << ")\n";
      printf(ss.str().c_str());
      Define(type);
   }

   StaticDefinition::~StaticDefinition()
   {
   }

   void StaticDefinition::Fetch(InstructionNode** target, InstructionElement* parameter)
   {
       *target = _Definition;
   }


   void StaticDefinition::Define(InstructionNode* type)
   {
      _Definition = type;
   }

}
