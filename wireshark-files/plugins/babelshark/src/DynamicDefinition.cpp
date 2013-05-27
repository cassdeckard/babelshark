// $Id$

#include "DynamicDefinition.h"
#include "DataDictionary.h"
#include <sstream>

#include <cstdio>

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
       // add to _Subjects
       if (_Subjects.count(parameter) == 0)
       {
           _Subjects.insert(std::make_pair(parameter, target));
           parameter->Attach(this);
       }
       else // TODO: what to do here? Throw an exception?
       {
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
      if (_Definitions.count(parameter) == 0)
      {
          _Definitions.insert(std::make_pair(parameter, typeDef));
      }
      else // TODO: what to do here? Throw an exception?
      {
      }
   }


   void DynamicDefinition::Update(Subject* subject)
   {
      std::stringstream ss;
      ss << "DynamicDefinition.Update( {" << subject << "} : ";

       // look up subject in our list
      InstructionElement* subjElem;
      // TODO: figure out better way to do this. Maybe have an inverse of the _Subjects map?
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
       if (_Definitions.count(parameter))
       {
           TypeDefinition* def = _Definitions[parameter];
           if (def) def->Fetch(&result);

           if (!result)
           {
               *(_Subjects[subjElem]) = DATA_DICT.NullInstruction();
           }
           else
           {
               // update pointer to appropriate InstructionSet
               *(_Subjects[subjElem]) = result;
           }

           ss << "{" << *(_Subjects[subjElem]) << "}\n";
       }
       else // TODO: what??
       {
           ss << "{ NOT FOUND }\n";
       }

      printf(ss.str().c_str());
   }

}
