// $Id$

#include "AliasedInstruction.h"
#include "DataDictionary.h"
#include <sstream>

#include <cstdio>
#include <cstring>

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
            std::stringstream ss;
            DATA_DICT.LookupType(&_RealSubject, _Alias);
            ss << _Name << " initializing " << _Alias << ", _RealSubject = {" << _RealSubject <<  "}\n";
            printf(ss.str().c_str());
        }
    }

    void AliasedInstruction::Initialize()
    {
        // Attach to parameter
        InstructionElement* param = DATA_DICT.LookupVariable(_ParamName);
        std::stringstream ss;
        ss << _Name << " initializing " << _Alias << "(" << _ParamName << "), _RealSubject = {" << _RealSubject <<  "}";
        DATA_DICT.LookupType(&_RealSubject, _Alias, param);
        ss << " => {" << _RealSubject <<  "}\n";
        printf(ss.str().c_str());
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
