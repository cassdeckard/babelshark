/***********************************************
File : BabelSharkSupport.cpp
*************************************************/

#pragma once

#include "BabelSharkSupport.h"
#include "elements.h"
#include "TreeVisitor.h"
#include "DynamicTypeCollection.h"
//#include "StaticTypeCollection.h"

//TODO: After we clean-up the test code out of here, remove these includes.
#include "InstructionSet.h"
#include "DynamicTypeElement.h"
#include "DataDictionary.h"

namespace PDI
{

   /*** The CreateInstructionTreeAndFillDataDictionary function is called by 
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
   * Then it will call the DynamicTypeCollection::FillDataDictionary function
   * to fill the data dictionary with all of the dynamictypes that were 
   * in the PDI File. 
   * Then it will instantiate the a TreeVisitor to create the Instruction Tree.
   * Finally, it will call singleton destructors to delete the StaticTypeCollection
   * singleton and the DynamicTypeCollection singleton.
   * 
   * The two paramters passed into this function are needed by the TreeVisitor
   * constructor and accept function.
   ***/
   void CreateInstructionTreeAndFillDataDictionary(const Element& elemRoot, bool bDisplayOutputToScreen)
   {
      //Create a StaticTypeElement and add it to the collection for testing purposes.
      // TODO: Later, when we have the parser updated to parse the file, remove this.
        //Instruction* _TestInstruction;
        //_TestInstruction = new InstructionSet(1, "TestProtocol");
        BabelShark::InstructionSet* tempTree;

        // make a static type
        tempTree = new BabelShark::InstructionSet(1, "TestAck");
        tempTree->Add(new BabelShark::UintElement(32, "Status"));
        BabelShark::DataDictionary::Instance()->AddStatic("&ACK", tempTree);

        // make another static type
        tempTree = new BabelShark::InstructionSet(1, "TestInit");
        tempTree->Add(new BabelShark::UintElement(7, "Age"));
        tempTree->Add(new BabelShark::PadElement(56, "Pad"));
        BabelShark::DataDictionary::Instance()->AddStatic("&INIT", tempTree);

      //StaticTypeCollection::FillDataDictionary();

      //Create a DynamicTypeElement and add it to the collection for testing purposes.
      // TODO: Later, when we have the parser updated to parse the file, remove this.
      DynamicTypeElement dynElement;
      dynElement.SetName("BODY");
      DynamicTypeEntry dynTypeEntry;
      dynTypeEntry.first = "1";
      dynTypeEntry.second = "&ACK";
      dynElement.Insert(dynTypeEntry);
      dynTypeEntry.first = "2";
      dynTypeEntry.second = "&INIT";
      dynElement.Insert(dynTypeEntry);
      DynamicTypeCollection::Instance().Insert(dynElement);

      DynamicTypeCollection::Instance().FillDataDictionary();

      // Pass the second arguement as true, to see output statements written to the screen for unit testing purposes.
      TreeVisitor treeVisitor(elemRoot.Name(), bDisplayOutputToScreen);
      elemRoot.Accept(treeVisitor);

      //Destroy StaticTypeCollection singleton.
      DynamicTypeCollection::Release();
   }

} // End namespace
