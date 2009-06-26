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
           DataDictionary();

           ~DataDictionary();

           void AddVariable(std::string, InstructionElement*);

           void AddStatic(std::string, InstructionNode*);

           void AddDynamic(std::string, std::string, std::string, InstructionElement*);

           void LookupType(InstructionNode**, std::string, InstructionElement* );

           InstructionElement* LookupVariable(std::string);

		protected:

        private:
           std::map<std::string, InstructionElement*> _Variables;
           std::map<std::string, TypeDefinition*> _Types;
	};

}

#endif //DATA_DICTIONARY_H