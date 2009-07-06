// $Id$

#include "DynamicDefinition.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{

   DynamicDefinition::DynamicDefinition(InstructionNode* type, std::string parameter)
      : TypeDefinition(type, parameter)
   {
      std::stringstream ss;
      ss << "DynamicDefinition( {" << type << "}, " << parameter.c_str() << ")\n";
      printf(ss.str().c_str());
   }

   DynamicDefinition::~DynamicDefinition()
   {
   }

   void DynamicDefinition::Fetch(InstructionNode** target, InstructionElement* parameter)
   {
       int size = (int)_Subjects.size();

       // add to _Subjects
       _Subjects[parameter] = target;

       if ( (int)_Subjects.size() > size)
       {
           // Attach() to parameter
           parameter->Attach(this);
       }

       // the target will be updated when parameter changes and Notify()s us
       // but go ahead and start it off with a NullInstruction
       *target = DATA_DICT.NullInstruction();

   }

   void DynamicDefinition::Add(TypeDefinition* typeDef, std::string parameter)
   {
      std::stringstream ss;
      ss << "DynamicDefinition.Add( {" << typeDef << "}, " << parameter.c_str() << ")\n";
      printf(ss.str().c_str());
      _Definitions[parameter] = typeDef;
   }


   void DynamicDefinition::Update(Subject* subject)
   {
      std::stringstream ss;
      ss << "DynamicDefinition.Update( {" << subject << "} : ";

       // look up subject in our list
      InstructionElement* subjElem;
      for (std::map<InstructionElement*, InstructionNode**>::iterator it = _Subjects.begin(); it != _Subjects.end(); it++)
      {
    	  if ( (*it).first == subject )
    	  {
    		  subjElem = (*it).first;
    		  break;
    	  }
      }

       // look up value of subject
       std::string parameter = subjElem->SimpleDisplay();

      ss << "parameter('" << parameter << "') => ";

       InstructionNode* result = NULL;
       TypeDefinition* def = _Definitions[parameter];
       if ( def != NULL ) def->Fetch(&result);

       if ( result == NULL )
       {
           *(_Subjects[subjElem]) = DATA_DICT.NullInstruction();
       }
       else
       {
           // update pointer to appropriate InstructionSet
           *(_Subjects[subjElem]) = result;
       }

      ss << "{" << *(_Subjects[subjElem]) << "}\n";

      printf(ss.str().c_str());
   }

}
