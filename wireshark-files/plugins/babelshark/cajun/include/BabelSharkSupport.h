/***********************************************
File : BabelSharkSupport.h
*************************************************/

#pragma once
#include "Instruction.h"

namespace PDI
{
   class Element;

   /** The CreateInstructionTreeAndFillDataDictionary function is called by
   * the calling code (either the Main.cpp file in cajun test folder or the
   * dissector.cpp file in babelshark include folder) after the PDI file
   * has been read by the Read function.
   *
   * The purpose of this function is to simplify the calling code, so
   * it doesn't need to know the details about creating the instruction
   * tree or about about filling the data dictionary.  For example, it
   * is important that the Data Dictionary is filled before the
   * Instruction Tree is created.  This function will ensure that happens.
   *
   * First it will call the StaticTypeCollection::FillDataDictionary
   * function to fill the Data Dictionary with all the statictypes that were
   * in the PDI File.
   * Then it will call the DynamicTypeDeclarationCollection::FillDataDictionary function
   * to fill the data dictionary with all of the dynamictypes that were
   * in the PDI File.
   * Then it will instantiate the a TreeVisitor to create the Instruction Tree.
   * Then it will call singleton destructors to delete the StaticTypeCollection
   * singleton and the DynamicTypeDeclarationCollection singleton.
   * Finally, it will return a pointer to the instruction tree.
   *
   * The two paramters passed into this function are needed by the TreeVisitor
   * constructor and accept function.  The first parameter is the root element
   * that was passed into the Read function.  The second parameter is a boolean
   * to determine if output should be displayed to the screen for debugging
   * purposes.
   ***/
   BabelShark::Instruction* CreateInstructionTreeAndFillDataDictionary(const Element& elemRoot, bool bDisplayOutputToScreen = false);

} // End namespace
