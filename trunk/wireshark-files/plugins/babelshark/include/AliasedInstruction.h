// $Id$

#ifndef ALIASED_INSTRUCTION_H
#define ALIASED_INSTRUCTION_H
#include "InstructionNode.h"
#include "DataDictionary.h"
#include "ListIterator.h"
#include <sstream>

#include <vector>

namespace BabelShark
{
	/** AliasedInstruction
      *
      * This class is used to create instances of Instructions with user-defined
      * static and dynamic types. Upon instantiation, it sets up a pointer to
      * the InstructionSet its type represents. For most methods, it merely delegates
      * the method to this InstructionSet.
      *
      * <b>Pattern roles:</b>
      *  - Proxy::Proxy
	  */
	class AliasedInstruction: public InstructionNode
	{
		public:
			/** Constructor
		      * This constructor is inherited from Instruction but should not
              * be used.
			  */
            AliasedInstruction(unsigned int size, char* name)
                : InstructionNode(size, name)
            {
                std::stringstream ss;
                ss << "AliasedInstruction(" << size << ", " << name << ")\n";
                printf(ss.str().c_str());
            }

            /** Constructor
              * In addition to normal Instruction() constructor behavior, this uses the given
              * alias and paramName to set its _RealSubject type to point to the correct
              * InstructionSet this AliasedInstruction will serve as a Proxy for.
              */
            AliasedInstruction(unsigned int size, char* name, std::string alias, std::string paramName = "")
                : InstructionNode(size, name)
            {
                InstructionElement* param = NULL;
                if (paramName.compare("") != 0)
                {
                    param = DataDictionary::Instance()->LookupVariable(paramName);
                }
                std::stringstream ss;
                ss << "AliasedInstruction(" << size << ", " << name << ", " << alias.c_str() << ")->_RealSubject = {" << _RealSubject <<  "}";
                DataDictionary::Instance()->LookupType(&_RealSubject, alias, param);
                ss << " => {" << _RealSubject <<  "}\n";
                printf(ss.str().c_str());
            }

			/** Destructor
				Empty desctructor class
			*/
            ~AliasedInstruction()
            {
            }

			/** GetChild
		      * Calls GetChild() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
			  */
            Instruction* GetChild() { return _RealSubject->GetChild(); }

            /** Add
              * Calls Add() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
              */
            void Add(Instruction* instruction) { _RealSubject->Add(instruction); }

            /** Interpret
              * Calls Interpret() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
              */
            unsigned int Interpret(char* buffer) {  return _RealSubject->Interpret(buffer); }

            /** Display
              * Calls Display() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
              */
            char* Display() { return _RealSubject->Display(); }

            /** CreateIterator
              * Calls CreateIterator() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
			  */
			Iterator* CreateIterator() { return _RealSubject->CreateIterator(); }

            /** GetSizeInBytes
              * Calls GetSizeInBytes() on its _RealSubject. Multiplies the result by
              * its _Size.
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
              */
            unsigned int GetSizeInBytes() { return _Size * _RealSubject->GetSizeInBytes(); }

            /** NumSubTrees
              * Calls NumSubTrees() on its _RealSubject
              *
              * <b>Pattern roles:</b>
              *  - Proxy::Request()
              */
            unsigned int NumSubtrees() { return _RealSubject->NumSubtrees(); }

		private:
            /** _RealSubject
              * The root of the Instruction tree this object will be a placeholder for.
              *
              * <b>Pattern roles:</b>
              *  - Proxy::realSubject
              */
			InstructionNode* _RealSubject;
	};
}

#endif //ALIASED_INSTRUCTION_H