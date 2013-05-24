// $Id$

// C++ headers
#include "DataDictionary.h"
#include "InstructionSet.h"
#include <sstream>

#include <cstdio>

namespace BabelShark
{
    /*
    DataDictionary* DataDictionary::_Instance = NULL;

    DataDictionary::DataDictionary()
    {
        _NullInstruction = new InstructionSet(0, "(No instruction)");
        std::stringstream ss;
        ss << "DD::_NullInstruction = {" << _NullInstruction << "}\n";
        printf(ss.str().c_str());
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
    */

    void DataDictionary::AddVariable(std::string alias, InstructionElement* variable)
    {
        _Variables[alias] = variable;
        std::stringstream ss;
        ss << "DD::_Variables[" << alias.c_str() << "] = {" << variable <<  "}\n";
        printf(ss.str().c_str());
    }

    void DataDictionary::AddStatic(std::string alias, InstructionNode* type)
    {

        if (_Types.count(alias) == 0)
        {
            // type doesn't exist yet; create it
            _Types[alias] = new StaticDefinition(type, "");
        }
        else
        {
            _Types[alias]->Define(type);
        }

        std::stringstream ss;
        ss << "DD::_Types[" << alias.c_str() << "] = {" << _Types[alias] <<  "}\n";
        printf(ss.str().c_str());
    }

    void DataDictionary::AddDynamic(std::string alias, std::string value, std::string typeName)
    {
        if (_Types.count(alias) == 0)
        {
            // type doesn't exist yet; create it
            _Types[alias] = new DynamicDefinition();
        }

        // if typeName doesn't already exist as a static type, create it
        if ( _Types[typeName] == NULL )
        {
            _Types[typeName] = new StaticDefinition();
        }

        // add new definition to dynamic type
        _Types[alias]->Add(_Types[typeName], value);
    }

    void DataDictionary::LookupType(InstructionNode** target, std::string alias, InstructionElement* parameter)
    {
        std::stringstream ss;
        ss << "DD::_Types[" << alias.c_str() << "]{" << _Types[alias] << "}->Fetch( {" << *target << "} , {" << parameter << "} )\n";
        printf(ss.str().c_str());
        _Types[alias]->Fetch(target, parameter);
    }

    InstructionElement* DataDictionary::LookupVariable(std::string alias)
    {
        return _Variables[alias];
    }

    void DataDictionary::ToInitialize(Instruction* instruction)
    {
        _ToInitialize.push_back(instruction);
    }

    void DataDictionary::Initialize()
    {
        for ( std::list<Instruction*>::iterator it = _ToInitialize.begin(); it != _ToInitialize.end(); it++ )
        {
            std::stringstream ss;
            ss << "DD initializing '" << (*it)->GetName() << "'\n";
            printf(ss.str().c_str());
            (*it)->Initialize();
        }
    }

} // namespace BabelShark
