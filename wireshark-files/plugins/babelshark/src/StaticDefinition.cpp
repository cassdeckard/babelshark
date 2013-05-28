// $Id$

#include "StaticDefinition.h"
#include <iostream>

using std::cout;
using std::endl;

namespace BabelShark
{

   StaticDefinition::StaticDefinition(InstructionNode* type, std::string parameter)
   {
      cout << "StaticDefinition( {" << type << "}, " << parameter.c_str() << ")" << endl;
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
