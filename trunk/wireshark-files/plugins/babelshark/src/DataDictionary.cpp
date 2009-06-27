// $Id$

// C++ headers
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    DataDictionary* DataDictionary::_Instance = NULL;

    DataDictionary::DataDictionary()
    {
	}

    DataDictionary::~DataDictionary()
    {
    }

    DataDictionary* DataDictionary::Instance()
    {
        if ( _Instance == NULL )
        {
            _Instance = new DataDictionary();
        }
        return _Instance;
    }

    void DataDictionary::AddVariable(std::string alias, InstructionElement* variable)
    {
        _Variables[alias] = variable;
        std::stringstream ss;
        ss << "_Variables[" << alias.c_str() << "] = {" << variable <<  "}\n";
        printf(ss.str().c_str());
    }

    void DataDictionary::AddStatic(std::string alias, InstructionNode* type)
    {
        _Types[alias] = new StaticDefinition(type, "");
        std::stringstream ss;
        ss << "_Types[" << alias.c_str() << "] = {" << _Types[alias] <<  "}\n";
        printf(ss.str().c_str());
    }

    void DataDictionary::AddDynamic(std::string alias, std::string value, std::string typeName, std::string typeParamName)
    {
        InstructionNode*    type;
        InstructionElement* typeParam;

        // get referred type param (if it exists)
        typeParam = this->LookupVariable(typeParamName);

        // get referred type
        this->LookupType(&type, typeName, typeParam);

        if (_Types.count(alias) == 0)
        {
            // type doesn't exist yet; create it
            _Types[alias] = new DynamicDefinition(type, value);
        }
        else
        {
            _Types[alias]->Add(type, value);
        }
    }

    void DataDictionary::LookupType(InstructionNode** target, std::string alias, InstructionElement* parameter)
    {
        std::stringstream ss;
        ss << "_Types[" << alias.c_str() << "]{" << _Types[alias] << "}->Fetch( {" << *target << "} , {" << parameter << "} )\n";
        printf(ss.str().c_str());
        _Types[alias]->Fetch(target, parameter);
    }

    InstructionElement* DataDictionary::LookupVariable(std::string alias)
    {
        return _Variables[alias];
    }

} // namespace BabelShark
