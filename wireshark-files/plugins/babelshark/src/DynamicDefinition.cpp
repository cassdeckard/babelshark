// $Id$

#include "DynamicDefinition.h"
#include <sstream>

namespace BabelShark
{

   DynamicDefinition::DynamicDefinition(InstructionNode* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
      std::stringstream ss;
      ss << "DynamicDefinition( {" << type << "}, " << parameter.c_str() << ")\n";
      printf(ss.str().c_str());
      _Definitions[parameter] = type;
   }

   DynamicDefinition::~DynamicDefinition()
   {
   }

   void DynamicDefinition::Fetch(InstructionNode** target, InstructionElement* parameter)
   {
       // add to _Subjects
       _Subjects[parameter] = target;

       // Attach() to parameter
       parameter->Attach(this);

       // the target will be updated when parameter changes and Notify()s us
   }

   void DynamicDefinition::Add(InstructionNode* type, std::string parameter)
   {
      std::stringstream ss;
      ss << "DynamicDefinition.Add( {" << type << "}, " << parameter.c_str() << ")\n";
      printf(ss.str().c_str());
      _Definitions[parameter] = type;
   }


   void DynamicDefinition::Update(InstructionElement* subject)
   {
       // look up value of subject
       std::string parameter = subject->SimpleDisplay();

       // update pointer to appropriate InstructionSet
       *(_Subjects[subject]) = _Definitions[parameter];
   }

}
