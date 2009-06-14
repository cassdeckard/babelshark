/**********************************************

Author: Julie Betlach, julie.betlach(a)gmail.com

***********************************************/
#pragma once


#include "UintElement.h"
#include "IntElement.h"
#include "BoolElement.h"
#include "FloatElement.h"
#include "AsciiElement.h"
#include "PadElement.h"
#include "InstructionSet.h"


#include <algorithm>
#include <map>
#include <sstream>
#include <string>

#include <iostream>
#include <fstream>


class TreeVisitor : public PDI::ConstVisitor
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
   TreeVisitor(const std::string& sName, bool bDisplayOutputToScreen = false) : 
      m_sName(sName),
      m_bDisplayOutputToScreen(bDisplayOutputToScreen),
      m_pInstruction(0)
   {
      m_CreateInstructionFuncMap["INT"] = &TreeVisitor::CreateInstruction<BabelShark::IntElement>;
      m_CreateInstructionFuncMap["UINT"] = &TreeVisitor::CreateInstruction<BabelShark::UintElement>;
      m_CreateInstructionFuncMap["BOOL"] = &TreeVisitor::CreateInstruction<BabelShark::BoolElement>;
      m_CreateInstructionFuncMap["FLOAT"] = &TreeVisitor::CreateInstruction<BabelShark::FloatElement>;
      m_CreateInstructionFuncMap["ASCII"] = &TreeVisitor::CreateInstruction<BabelShark::AsciiElement>;
      m_CreateInstructionFuncMap["PAD"] = &TreeVisitor::CreateInstruction<BabelShark::PadElement>;
   }

   BabelShark::Instruction* GetInstruction() { return m_pInstruction; }

private:
   template <typename InstructionTypeT>
   BabelShark::Instruction* CreateInstruction(unsigned int nSize, const std::string& sName)
   {
      char* s = const_cast<char*>(sName.c_str()); 
	  // This would be easier if std::string was the parameter type rather than char*.
      return new InstructionTypeT(nSize, s);
   }

   virtual void Visit(const PDI::Array& array) {
      if (m_bDisplayOutputToScreen)
      {
         std::cout << "This array node has been visited " << m_sName << ", dimension " << array.Dimension() << std::endl;
      }

      BabelShark::InstructionSet* pInstructionSet = new BabelShark::InstructionSet(array.Dimension(), (char*)m_sName.c_str()); // TODO: fix "char*"
      PDI::Array::const_iterator it(array.Begin()),
                                   itEnd(array.End());
      for (; it != itEnd; ++it)
      {
         TreeVisitor visitor(it->Name(), m_bDisplayOutputToScreen);
         it->Accept(visitor);

         pInstructionSet->Add(visitor.GetInstruction());
      }

      m_pInstruction = pInstructionSet;
   }

   // For PDI, we will always use strings for the values.
   virtual void Visit(const PDI::String& string) {
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
         if (m_bDisplayOutputToScreen)
         {
            std::cout << "This leaf node has been visited " << m_sName << " " << sType << " " << nSize << std::endl;
         }
      }
      
      CreateInstructionFunc func = it->second;
      m_pInstruction = (this->*func)(nSize, m_sName);
   }


   // For PDI, we won't need any of these.
   virtual void Visit(const PDI::Null& null) { throw std::runtime_error("ERROR: should never see NULL element"); }

   typedef BabelShark::Instruction* (TreeVisitor::*CreateInstructionFunc)(unsigned int, const std::string&);
   typedef std::map<std::string, CreateInstructionFunc> CreateInstructionFuncMap;

   CreateInstructionFuncMap m_CreateInstructionFuncMap;

   std::string m_sName;
   BabelShark::Instruction* m_pInstruction;
   bool m_bDisplayOutputToScreen;
};
