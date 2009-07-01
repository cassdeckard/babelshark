// $Id$

#include "AliasedInstruction.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    // OLD AND BUSTED
    AliasedInstruction::AliasedInstruction(unsigned int size, char* name, std::string alias, std::string paramName)
	    : InstructionNode(size, name),
          _Alias(alias),
          _ParamName(paramName)
    {
        _RealSubject = DataDictionary::Instance()->NullInstruction();
        if (_ParamName.compare("") != 0)
        {
            // dynamic type; put in DD initialize list
            DataDictionary::Instance()->ToInitialize(this);
        }
        else
        {
            // static type; go ahead and initialize
            std::stringstream ss;
            DataDictionary::Instance()->LookupType(&_RealSubject, _Alias);
            ss << _Name << " initializing " << _Alias << ", _RealSubject = {" << _RealSubject <<  "}";
            printf(ss.str().c_str());
        }
    }

    // NEW HOTNESS
    AliasedInstruction::AliasedInstruction(std::string size, std::string name, std::string alias, std::string paramName)
        : InstructionNode(size, name),
          _Alias(alias),
          _ParamName(paramName)
    {
        _RealSubject = DataDictionary::Instance()->NullInstruction();
        if (_ParamName.compare("") != 0)
        {
            // dynamic type; put in DD initialize list
            DataDictionary::Instance()->ToInitialize(this);
        }
        else
        {
            // static type; go ahead and initialize
            std::stringstream ss;
            DataDictionary::Instance()->LookupType(&_RealSubject, _Alias);
            ss << _Name << " initializing " << _Alias << ", _RealSubject = {" << _RealSubject <<  "}";
            printf(ss.str().c_str());
        }
    }

    void AliasedInstruction::Initialize()
    {
        // Attach to parameter
        InstructionElement* param = DataDictionary::Instance()->LookupVariable(_ParamName);
        std::stringstream ss;
        ss << _Name << " initializing " << _Alias << "(" << _ParamName << "), _RealSubject = {" << _RealSubject <<  "}";
        DataDictionary::Instance()->LookupType(&_RealSubject, _Alias, param);
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
