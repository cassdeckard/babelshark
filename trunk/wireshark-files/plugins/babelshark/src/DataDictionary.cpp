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

    void DataDictionary::AddStatic(std::string alias, InstructionNode* type)
    {
        _Types[alias] = new StaticDefinition(type, 0);
    }

    void DataDictionary::AddDynamic(std::string alias, std::string parameter, std::string typeName, InstructionElement* typeParam = NULL)
    {
        InstructionNode* type;
        this->LookupType(&type, typeName, typeParam); // get referred type
        _Types[alias]; // "touch" to instantiate
        _Types[alias]->Add(type, parameter);
    }

    void DataDictionary::LookupType(InstructionNode** target, std::string alias, InstructionElement* parameter = NULL)
    {
        _Types[alias]->Fetch(target, parameter);
    }

    InstructionElement* DataDictionary::LookupVariable(std::string label)
    {
        return _Variables[label];
    }

} // namespace BabelShark
