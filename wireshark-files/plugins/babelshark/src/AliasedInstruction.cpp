// $Id$

#include "AliasedInstruction.h"
#include "DataDictionary.h"
#include <iostream>

#include <cstring>

using std::cout;
using std::endl;

namespace BabelShark
{
    AliasedInstruction::AliasedInstruction(std::string size, std::string name, std::string alias, std::string paramName)
        : InstructionNode(size, name),
          _Alias(alias),
          _ParamName(paramName)
    {
        _RealSubject = DATA_DICT.NullInstruction();
        if (_ParamName.compare("") != 0)
        {
            // dynamic type; put in DD initialize list
            DATA_DICT.ToInitialize(this);
        }
        else
        {
            // static type; go ahead and initialize
			//TODO: DAN  pass in the Dynamic variable usage into the LookupType function
            DATA_DICT.LookupType(&_RealSubject, _Alias);
            cout << _Name << " initializing " << _Alias << ", _RealSubject = {" << _RealSubject <<  "}" << endl;
        }
    }

    void AliasedInstruction::Initialize()
    {
        // Attach to parameter
        InstructionElement* param = DATA_DICT.LookupVariable(_ParamName);
        cout << _Name << " initializing " << _Alias << "(" << _ParamName << "), _RealSubject = {" << _RealSubject <<  "}";
        DATA_DICT.LookupType(&_RealSubject, _Alias, param);
        cout << " => {" << _RealSubject <<  "}" << endl;
    }

    char* AliasedInstruction::Display()
    {
        // Append AliasedInstruction's name to Display
        static char* result;
        std::string resultStr = _Name + " : " + _RealSubject->Display();
        result = new char[resultStr.length() + 1];
        memcpy(result, resultStr.c_str(), resultStr.length());
        result[resultStr.length()] = 0; // null terminator
        return result;
    }

}
