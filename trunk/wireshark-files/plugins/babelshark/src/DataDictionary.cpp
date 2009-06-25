// $Id$

// C++ headers
#include "DataDictionary.h"

namespace BabelShark
{
    DataDictionary::DataDictionary()
    {
	}

    DataDictionary::~DataDictionary()
    {
	}

    void DataDictionary::AddVariable(std::string alias, InstructionElement* variable)
    {
        _Variables[alias] = variable;
    }

    void DataDictionary::AddStatic(std::string alias, Instruction* type)
    {
        _Types[alias] = new StaticDefinition(type, 0);
    }

    void DataDictionary::AddDynamic(std::string alias, std::string parameter, std::string typeName, InstructionElement* typeParam = NULL)
    {
        Instruction* type = this->LookupType(typeName, typeParam); // get referred type
        _Types[alias]; // "touch" to instantiate
        _Types[alias]->Add(type, parameter);
    }

    Instruction* DataDictionary::LookupType(std::string alias, InstructionElement* parameter = NULL)
    {
        return _Types[alias]->Fetch(parameter);
    }

    InstructionElement* DataDictionary::LookupVariable(std::string label)
    {
        return _Variables[label];
    }

} // namespace BabelShark
