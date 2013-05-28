// $Id$

// C++ headers
#include "DataDictionary.h"
#include "InstructionSet.h"
#include <iostream>

using std::cout;
using std::endl;

namespace BabelShark
{
    void DataDictionary::AddVariable(std::string alias, InstructionElement* variable)
    {
        _Variables[alias] = variable;
        cout << "DD::_Variables[" << alias.c_str() << "] = {" << variable <<  "}" << endl;
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
        cout << "DD::_Types[" << alias.c_str() << "] = {" << _Types[alias] <<  "}" << endl;
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
        cout << "DD::_Types[" << alias.c_str() << "]{" << _Types[alias] << "}->Fetch( {" << *target << "} , {" << parameter << "} )" << endl;
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
            cout << "DD initializing '" << (*it)->GetName() << "'" << endl;
            (*it)->Initialize();
        }
    }

} // namespace BabelShark
