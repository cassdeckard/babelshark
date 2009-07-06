/***********************************************
File : BabelSharkSupport.cpp
*************************************************/

#pragma once

#include "BabelSharkSupport.h"
#include "elements.h"
#include "TreeVisitor.h"
#include "DynamicTypeDeclarationCollection.h"
#include "StaticTypeDeclarationCollection.h"

//TODO: After we clean-up the test code out of here, remove these includes.
#include "InstructionSet.h"
#include "DynamicTypeDeclarationElement.h"
#include "DataDictionary.h"

namespace PDI
{
   BabelShark::Instruction* CreateInstructionTreeAndFillDataDictionary(const Element& elemRoot, bool bDisplayOutputToScreen)
   {
      StaticTypeDeclarationCollection::Instance().FillDataDictionary();
      DynamicTypeDeclarationCollection::Instance().FillDataDictionary();

      // Pass the second arguement as true, to see output statements written to the screen for unit testing purposes.
      TreeVisitor TreeVisitor(elemRoot.Name(), bDisplayOutputToScreen);
      elemRoot.Accept(TreeVisitor);

      //Destroy the singletons to prepare us for another file.
      StaticTypeDeclarationCollection::Release();
      DynamicTypeDeclarationCollection::Release();

      //This is here so we can use the debugger to view the instruction tree that was created.
      BabelShark::Instruction* pRootInstruction = TreeVisitor.GetInstruction();

	   return pRootInstruction;

   }

} // End namespace
