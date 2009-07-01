// $Id$

#include "AliasedInstruction.h"
#include "DataDictionary.h"
#include <sstream>

namespace BabelShark
{
    // OLD AND BUSTED
    AliasedInstruction::AliasedInstruction(unsigned int size, char* name)
	    : InstructionNode(size, name)
    {
	    std::stringstream ss;
	    ss << "AliasedInstruction(" << size << ", " << name << ")\n";
	    printf(ss.str().c_str());
    }

    // OLD AND BUSTED
    AliasedInstruction::AliasedInstruction(unsigned int size, char* name, std::string alias, std::string paramName)
	    : InstructionNode(size, name)
    {
        InstructionElement* param = NULL;
        if (paramName.compare("") != 0)
        {
            param = DataDictionary::Instance()->LookupVariable(paramName);
        }
        std::stringstream ss;
        ss << "AliasedInstruction(" << size << ", " << name << ", " << alias.c_str() << ")->_RealSubject = {" << _RealSubject <<  "}";
        DataDictionary::Instance()->LookupType(&_RealSubject, alias, param);
        ss << " => {" << _RealSubject <<  "}\n";
        printf(ss.str().c_str());
    }

    // NEW HOTNESS
    AliasedInstruction::AliasedInstruction(std::string size, std::string name)
        : InstructionNode(size, name)
    {
        std::stringstream ss;
        ss << "AliasedInstruction(" << size << ", " << name << ")\n";
        printf(ss.str().c_str());
    }

    // NEW HOTNESS
    AliasedInstruction::AliasedInstruction(std::string size, std::string name, std::string alias, std::string paramName)
        : InstructionNode(size, name)
    {
        InstructionElement* param = NULL;
        if (paramName.compare("") != 0)
        {
            param = DataDictionary::Instance()->LookupVariable(paramName);
        }
        std::stringstream ss;
        ss << "AliasedInstruction(" << size << ", " << name << ", " << alias.c_str() << ")->_RealSubject = {" << _RealSubject <<  "}";
        DataDictionary::Instance()->LookupType(&_RealSubject, alias, param);
        ss << " => {" << _RealSubject <<  "}\n";
        printf(ss.str().c_str());
    }

}
