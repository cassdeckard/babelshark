// $Id$

#ifndef DATA_DICTIONARY_H
#define DATA_DICTIONARY_H

#include "Instruction.h"
#include "InstructionElement.h"
#include "TypeDefinition.h"
#include "StaticDefinition.h"
#include "DynamicDefinition.h"
#include <map>

namespace BabelShark
{
	class DataDictionary
	{
        public:
           static DataDictionary* Instance();

           void AddVariable(std::string, InstructionElement*);

           void AddStatic(std::string, InstructionNode*);

           void AddDynamic(std::string, std::string, std::string, std::string);

           void LookupType(InstructionNode**, std::string, InstructionElement* = NULL );

           InstructionElement* LookupVariable(std::string);

        protected:
           DataDictionary();

           ~DataDictionary();

        private:
           static DataDictionary* _Instance;
           std::map<std::string, InstructionElement*> _Variables;
           std::map<std::string, TypeDefinition*> _Types;
	};

}

#endif //DATA_DICTIONARY_H