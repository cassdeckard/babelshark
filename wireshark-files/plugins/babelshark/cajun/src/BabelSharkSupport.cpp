/***********************************************
File : BabelSharkSupport.cpp
*************************************************/

#include "BabelSharkSupport.h"
#include "elements.h"
#include "TreeVisitor.h"
#include "DynamicTypeDeclarationCollection.h"
#include "StaticTypeDeclarationCollection.h"

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
