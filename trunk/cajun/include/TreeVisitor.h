#pragma once

#include "UintElement.h"
#include "AsciiElement.h"
#include "BoolElement.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>

// delete these later when I remove the std::cout calls.
#include <iostream>
#include <fstream>


class TreeVisitor : public json::ConstVisitor
{
public:
/*type     := 'UINT'
         |  'INT'
         |  'BOOL'
         |  'FLOAT'
         |  'ASCII'
         |  'PAD'
         |  array
*/

   //A parameter should be added to the constructor that specifies how long the buffer is and checked appropriately.
   TreeVisitor()
   {
//      m_CreateInstructionFuncMap["INT"] = &TreeVisitor::CreateInstruction<BabelShark::IntElement>;
      m_CreateInstructionFuncMap["UINT"] = &TreeVisitor::CreateInstruction<BabelShark::UintElement>;
      m_CreateInstructionFuncMap["BOOL"] = &TreeVisitor::CreateInstruction<BabelShark::BoolElement>;
//      m_CreateInstructionFuncMap["FLOAT"] = &TreeVisitor::CreateInstruction<BabelShark::FloatElement>;
      m_CreateInstructionFuncMap["ASCII"] = &TreeVisitor::CreateInstruction<BabelShark::AsciiElement>;
//      m_CreateInstructionFuncMap["PAD"] = &TreeVisitor::CreateInstruction<BabelShark::PadElement>;
   }

private:

   template <typename InstructionTypeT>
   void CreateInstruction(unsigned int nSize, const std::string& sName)
   {
      char* s = const_cast<char*>(sName.c_str()); 
	  // This would be easier if std::string was the parameter type rather than char*.
      InstructionTypeT* pInstruction = new InstructionTypeT(nSize, s);
      
   }

   virtual void Visit(const json::Array& array) {
      json::Array::const_iterator it(array.Begin()),
                                  itEnd(array.End());
      for (; it != itEnd; ++it)
      {
         it->Accept(*this); // indirectly recursive
      }
   }

   virtual void Visit(const json::Object& object) {
      json::Object::const_iterator it(object.Begin()),
                                   itEnd(object.End());
      for (; it != itEnd; ++it)
      {
         it->element.Accept(*this); // indirectly recursive
      }
   }

   // For PDI, we will always use strings for the values.
   virtual void Visit(const json::String& string) {
      std::istringstream ss(string);

      std::string sType;
      int nSize;
      ss >> sType >> nSize;

      CreateInstructionFuncMap::const_iterator it = m_CreateInstructionFuncMap.find(sType);
      if (it == m_CreateInstructionFuncMap.end())
      {
         std::string sException = "use of undefined type: " + sType;
         throw std::exception(sException.c_str());
      }
      else
      {
         std::cout << "This leaf node has been visited " << sType << std::endl;
      }
      
      CreateInstructionFunc func = it->second;
      (this->*func)(nSize, sType);


      

      // case UINT

      // case ASCII
   }


   // For PDI, we won't need any of these.
   virtual void Visit(const json::Null& null) {}

   typedef void (TreeVisitor::*CreateInstructionFunc)(unsigned int, const std::string&);
   typedef std::map<std::string, CreateInstructionFunc> CreateInstructionFuncMap;

   CreateInstructionFuncMap m_CreateInstructionFuncMap;

};
