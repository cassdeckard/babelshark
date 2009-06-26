// $Id$

#include "DynamicDefinition.h"

namespace BabelShark
{

   DynamicDefinition::DynamicDefinition(InstructionNode* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
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
      _Definitions[parameter] = type;
   }


   void DynamicDefinition::Update(InstructionElement* subject)
   {
       std::string parameter = "";

       // look up value of subject
       // TODO

       // update pointer to appropriate InstructionSet
       _Subjects[subject] = &_Definitions[parameter];
   }

}
