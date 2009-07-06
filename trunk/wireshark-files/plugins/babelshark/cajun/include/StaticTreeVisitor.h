/***********************************************

Author: Julie Betlach

Code written for a project for Washington University,
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

File Name: StaticTreeVisitor.h

File Description: The StaticTreeVisitor.h file is a part of the PDI parser.  It provides the implementation
of the StaticTreeVisitor class.

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

#include "TreeVisitor.h"

#include <algorithm>
#include <map>
#include <sstream>
#include <string>

#include <iostream>
#include <fstream>

/** The StaticTreeVisitor class is used to visit (iterate over) each item in a Statictype Tree.
  * A statictype tree is created for each statictype in a PDI File.  
  * When a node on the tree is visited, an instruction is created
  * forming an Instruction Tree.  The Wireshark dissector will use the instruction tree created 
  * by this class when it is referred to by its alias in another instruction.
  *
  * Usage: After a file has been read in by calling the following parser functions...
  *       Element elemRoot = DisplayElement();
  *       Reader::Read(elemRoot, std::ifstream("AvatarsInRoom.txt"));
  * then the following function can be called to create a statictype instruction tree.
  *       StaticTreeVisitor StaticTreeVisitor(elemRoot.Name());
  * Note that the root element name must be passed into the StaticTreeVisitor in order to get the 
  * name of the statictype to be included in the first instruction in the instruction tree.
  *
  * If a second parameter is provided, which is boolean, this will be used to determine if
  * unit test / debug data should be written to cout.  If the parameter is true then data will
  * be displayed.  If the parameter is false, or is not provided, then data will not be displayed.
  *
  * StaticTreeVisitor inherits from TreeVisitor.  The only difference is that when the StaticTreeVisitor
  * Visit function is called on an array, the resultant InstructionSet is added to the DataDictionary.
  ***/
class StaticTreeVisitor : public TreeVisitor
{
public:
    /** This is the constructor for StaticTreeVisitor class.
      *
      * @param sName
      *   the name of the root node.
      * @param bDisplayOutputToScreen
      *   (optional) should be true if you want output to the screen for testing
      *
      * A function map is initialized in the constructor using a template.
      * This will make the addition of new types easier.
      ***/
   StaticTreeVisitor(const std::string& sName, bool bDisplayOutputToScreen = false) :
      TreeVisitor(sName, bDisplayOutputToScreen)
   {

   }

private:
  
   /** Visit() iterates over all items in the array. It calls a visit function
     * on each item.  It passes in the name of the array for the same reason that we needed to pass the name of
     * the root node into the constructor, so that it would be available to use when we create the instruction.
     *
     * Each item in the array is added to an instruction set.
     *
     * This function is a duplicate of the TreeVisitor Visit function on an array, however, with two 
     * differences.  The InstructionSet is added to the DataDictionary at the end of the function.
     * Also this function does not call itself when an array is inside an array.  Instead
     * it calls the TreeVisitor function this is because we don't want to add the internal array
     * to the DataDictionary.
     ***/
   virtual void Visit(const PDI::Array& array) 
   {
      if (m_bDisplayOutputToScreen)
      {
         std::cout << "This array node has been visited " << m_sName << ", dimension " << array.Dimension() << std::endl;
      }

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
		DATA_DICT.AddStatic(m_sName, pInstructionSet);
   }
};
