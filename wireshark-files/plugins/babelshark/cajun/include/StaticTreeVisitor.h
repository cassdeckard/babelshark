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
  * This class is derived from ConstVisitor, so likewise, its functions do not modify the nodes
  * that it is visiting.  If you need to extend the functionality of this class to modify the nodes,
  * then change this class to be derived from the Visitor class.
  *
  * <pre>
  * Design Pattern: Visitor
  * Design Pattern Role: ConcreteVisitor
  * Other Participants: 
  *    The ConstVisitor class plays the Visitor role.
  *    The TreeVisitor class plays the ConcreteVisitor role.
  *    The abstract Element class plays the Element role.
  *    The Array class plays the ConcreteElement role.
  *    The DisplayElement class plays the ConcreteElement role.
  *    The Null class plays the ConcreteElement role.
  * </pre>
  *
  * Usage: After a file has been read in by calling the following parser functions...
  *       Element elemRoot = DisplayElement();
  *       Reader::Read(elemRoot, std::ifstream("AvatarsInRoom.txt"));
  * then the following function can be called to create a statictype instruction tree
  * and add it to the DataDictionary:
  *       StaticTreeVisitor StaticTreeVisitor(elemRoot.Name());
  * Note that the root element name must be passed into the StaticTreeVisitor in order to get the 
  * name of the statictype to be included in the first instruction in the instruction tree.
  *
  * If a second parameter is provided, which is boolean, this will be used to determine if
  * unit test / debug data should be written to cout.  If the parameter is true then data will
  * be displayed.  If the parameter is false, or is not provided, then data will not be displayed.
  *
  * StaticTreeVisitor inherits from TreeVisitor.  The major difference is that when the StaticTreeVisitor
  * Visit function is called on an array, the resultant InstructionSet is added to the DataDictionary.
  * A minor difference is that the StaticTreeVisitor Visit(Array) function does create a StaticTreeVisitor
  * recursively, instead it creates a TreeVisitor.
  */
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
      */
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
     * differences.  The InstructionSet is added to the DataDictionary at the end of this function.
     * Also this function does not create a new StaticTreeVisitor when it discovers an array inside an array.  
     * Instead instead it creates a TreeVisitor. This is because we don't want to add any internal arrays
     * to the DataDictionary on their own.  We want them to be a part of the one entry for this statictype.
     */
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
         TreeVisitor visitor(it->Name(), m_bDisplayOutputToScreen);  // Use base class.
         it->Accept(visitor);

         pInstructionSet->Add(visitor.GetInstruction());
      }

      m_pInstruction = pInstructionSet;
		DATA_DICT.AddStatic(m_sName, pInstructionSet);  // Add InstructionSet to Data Dictionary.
   }
};
