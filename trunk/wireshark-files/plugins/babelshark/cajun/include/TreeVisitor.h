/***********************************************

Author: Julie Betlach

Code written for a project for Washington University,
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

File Name: TreeVisitor.h

File Description: The TreeVisitor.h file is a part of the PDI parser.  It provides the implementation
of the TreeVisitor class.

*************************************************/
#pragma once


#include "UintElement.h"
#include "IntElement.h"
#include "BoolElement.h"
#include "FloatElement.h"
#include "AsciiElement.h"
#include "PadElement.h"
#include "InstructionSet.h"
#include "AliasedInstruction.h"

#include "visitor.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

/** The TreeVisitor class is used to visit (iterate over) each item in the Tree which is created by
  * reading in a file in PDI format.  When a node on the tree is visited, an instruction is created
  * in the Instruction Tree.  The Wireshark dissector will use the instruction tree created by this class.
  *
  * Usage: After a file has been read in by calling the following parser functions...
  *       Element elemRoot = DisplayElement();
  *       Reader::Read(elemRoot, std::ifstream("AvatarsInRoom.txt"));
  * then the following function can be called to create an instruction tree.
  *       TreeVisitor treeVisitor(elemRoot.Name());
  * Note that the root element name must be passed into the TreeVisitor in order to get the first
  * name from the file to be included in the first instruction in the instruction tree.
  *
  * If a second parameter is provided, which is boolean, this will be used to determine if
  * unit test / debug data should be written to cout.  If the parameter is true then data will
  * be displayed.  If the parameter is false, or is not provided, then data will not be displayed.
  ***/
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
***/

    /** This is the constructor for TreeVisitor class.
      *
      * @param sName
      *   the name of the root node.
      * @param bDisplayOutputToScreen
      *   (optional) should be true if you want output to the screen for testing
      *
      * A function map is initialized in the constructor using a template.
      * This will make the addition of new types easier.
      ***/
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

   /** GetInstruction() returns a pointer to an instruction.
     *
     ***/
   BabelShark::Instruction* GetInstruction() { return m_pInstruction; }

private:
   /** CreateInstruction() uses a template to reduce code size and to make it easier to
     * add new types.  There are 3 pieces of data that an instruction needs: name, type, size.
     * Size and name are passed in as parameters.  The Type is known because this is a template function
     * and it is InstructionTypeT.
     *
     * @param sSize
     * @param sName
     ***/
   template <typename InstructionTypeT>
   BabelShark::Instruction* CreateInstruction(const std::string& sSize, const std::string& sName, const std::string& sVariable)
   {
      return new InstructionTypeT(sSize, sName, sVariable);
   }

   /** Visit() uses iterates over all items in the array. It calls a visit function
     * on each item.  It passes in the name of the array for the same reason that we needed to pass the name of
     * the root node into the constructor.  So that it would be available to use when we create the instruction.
     *
     * Each item in the array is added to an instruction set.
     ***/
   virtual void Visit(const PDI::Array& array) 
   {
      if (m_bDisplayOutputToScreen)
      {
         std::cout << "This array node has been visited " << m_sName << ", dimension " << array.Dimension() << std::endl;
      }

      //TODO: (JULIE) Currently this passes a number into InstructionSet constructor.
      //              After InstructionSet is changed to take a string, uncomment row below and delete this kluge.
/*kluge start
      std::istringstream ss(array.Dimension());

      size_t nDimension;
      ss >> nDimension;
      BabelShark::InstructionSet* pInstructionSet = new BabelShark::InstructionSet(nDimension, (char*)m_sName.c_str()); // TODO: fix "char*"
kluge end
*/
      BabelShark::InstructionSet* pInstructionSet = new BabelShark::InstructionSet(array.Dimension(), m_sName);
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

   /** Visit() is used to visit a DisplayElement.
     * It creates one instruction for the DisplayElement.  It uses a template
     * in order to reduce code.  It looks in the function map for a known type
     * and then calls the appropriate function to create the instruction that
     * matches the desired type.  For example, if ASCII is the type, then an
     * AsciiElement instruction is created and added to the instruction tree.
     ***/
   virtual void Visit(const PDI::DisplayElement& string) {
      std::istringstream ss(string);

      // DISPLAY_ELEMENT can be any one of the following formats:
      // "NameSimple" : "Type Size"
      // "NameSimple" : "Type Size $Optional_Variable"
      // "NameStaticTypeUsage" : "&Alias Size"
      // "NameDynamicTypeUsage" : "&Alias($Variable) Size"

      char cPeekCharacter = ss.peek();

      if (cPeekCharacter == '&')
      {
         // This is either a StaticType usage or a DynamicType usage:
         // "NameStaticTypeUsage" : "&Alias Size"
         // "NameDynamicTypeUsage" : "&Alias($Variable) Size"

         // Split the stream into two different tokens defined by a space between them.  The second one is size.
         std::string sAlias;
         std::string sSize;
         ss >> sAlias >> sSize;

         // The following code does this...
         //1) Determine if this is a static or dynamic usage by looking for the (
         //2) If this is static, then create an AliasedInstruction and pass in the nSize, sAlias.
         //3) If this is dynamic, then
         //3a) Split Alias into two strings (one being &Alias and the other being $Variable, and strip off the parenthesis)
         //3b) Create an AliasedInstruction and pass in the nSize, sAlias, $Variable.

         size_t nLocationOfOpenParen = sAlias.find('(');
         size_t nLocationOfCloseParen = sAlias.find(')');
		 if ((nLocationOfOpenParen != std::string::npos) & (nLocationOfCloseParen != std::string::npos))
         {
            // This is a dynamic Aliased Instruction (It has a parameter).
            std::string sVariable = sAlias.substr(nLocationOfOpenParen+1, nLocationOfCloseParen-nLocationOfOpenParen-1);
            sAlias = sAlias.substr(0, nLocationOfOpenParen);
			m_pInstruction = new BabelShark::AliasedInstruction(sSize, m_sName, sAlias, sVariable);
         }
         else
         {
            // This is a static Aliased Instruction (It does not have a parameter).
            m_pInstruction = new BabelShark::AliasedInstruction(sSize, m_sName, sAlias);
         }

      }
      else
      {
         // This is a Simple Display Element in one of the following layouts:
         // "NameSimple" : "Type Size"
         // "NameSimple" : "Type Size $Optional_Variable"

         std::string sType;
         std::string sSize;
         std::string sVariableName;
         ss >> sType >> sSize >> sVariableName;

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
               std::cout << "This leaf node has been visited " << m_sName << " " << sType << " " << sSize << " " << sVariableName << std::endl;
            }
         }

         CreateInstructionFunc func = it->second;
         m_pInstruction = (this->*func)(sSize, m_sName, sVariableName);
      }
   }

   /** Visit() is used to visit a NULL_ELEMENT.  This was kept in for completeness.
     * It's a good idea to still have the NULL_ELEMENT enum value so we can default the type of a new element to
     * NULL_ELEMENT.  However, we should never be visiting a NULL_ELEMENT, so an exception in thrown.
     ***/
   virtual void Visit(const PDI::Null& null) { throw std::runtime_error("ERROR: should never see NULL element"); }

   typedef BabelShark::Instruction* (TreeVisitor::*CreateInstructionFunc)(const std::string&, const std::string&, const std::string&);
   typedef std::map<std::string, CreateInstructionFunc> CreateInstructionFuncMap;

   CreateInstructionFuncMap m_CreateInstructionFuncMap;

   std::string m_sName;
   BabelShark::Instruction* m_pInstruction;  // This is used so that one visit function may see the instruction from another.
   bool m_bDisplayOutputToScreen;
};
